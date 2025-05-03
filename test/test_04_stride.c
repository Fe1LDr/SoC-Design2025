#include "boot.h"
#include "converter.h"
#include "irq.h"
#include "regs.h"
#include <stdio.h>
#include <stdlib.h>

#include "set_tests.h"

void layout_with_stride(const uint8_t *src, uint8_t *dst, int line_count, int image_payload, int stride) {
    for (int row = 0; row < line_count; row++) {
        memcpy(dst + row * stride,
               src + row * image_payload,
               image_payload);
    }
}

int sim_main() {
    int rc = 0;

    int stride = 256;
    int image_payload = 192;
    int line_length = image_payload / 4;
    int stride_lines = 8;

    static uint8_t pJpegImageStrided[4096];

    layout_with_stride(pJpegImage, pJpegImageStrided, stride_lines, image_payload, stride);

    jpeg_setup_decoder();

    dma_set_reader_channel(line_length, stride_lines, 16);
    write_mem_32( &dma->reader.addr, pJpegImageStrided );
    dma_set_writer_channel(line_length, stride_lines, 0);
    dma_set_both_start();
    dma_wait_writer();

    jpeg_wait_idle();

    uint16_t width = jpeg_size_width();
    uint16_t height = jpeg_size_height();
    uint32_t bgr_filesize = 3 * width * height;

    convert_to_bmp( pSocAxilOutBuffer, pInnerDecodeBuffer, width, height );

    char filename[128];
    uint32_t bmp_filesize = bgr_filesize + 54;
    snprintf(filename, sizeof(filename), "%s/img_%luB_%ux%u.bmp\0",
                                        "build", 4 * kImageSize, width, height);
    printf("filename %s\n", filename);
    FILE* fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("The bmp file is not opened. The program will now exit.\n");
        return ++rc;
    }
    fwrite(pInnerDecodeBuffer, 1, bmp_filesize, fptr);
    fclose(fptr);

    if (cmpbuf(pSocAxilOutBuffer, pGoldenImage, bgr_filesize)) {
        printf("\nError while compare decoded BGR with GOLDEN one\n");
        return ++rc;
    }

    return rc;
}
