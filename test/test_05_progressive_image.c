#include "boot.h"
#include "converter.h"
#include "irq.h"
#include "regs.h"
#include <stdio.h>
#include <stdlib.h>

#include "set_tests.h"

int sim_main() {
    int rc = 0;
    int line_length = 32;
    int line_count = kImageSize / line_length + 1;

    jpeg_setup_decoder();

    wfi_decode = true;

    dma_set_reader_channel(line_length, line_count, 0);
    dma_set_writer_channel(line_length, line_count, 0);

    dma_set_both_start();
    dma_wait_writer();

    wait_decode_irq();

    if (!jpeg_check_progressive()) {
        return ++rc;
    }

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
