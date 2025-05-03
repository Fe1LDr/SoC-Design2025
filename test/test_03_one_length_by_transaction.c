#include "boot.h"
#include "converter.h"
#include "irq.h"
#include "regs.h"
#include <stdio.h>
#include <stdlib.h>

#include "set_tests.h"

int sim_main() {
    int rc = 0;
    int line_length = 1; // 4 bytes - 1 word
    int line_count = kImageSize / line_length + 1;

    jpeg_setup_decoder();

    /* prepare flags for irq wait */
    wfi_reader = true;
    wfi_writer = true;
    wfi_decode = true;
    dma_enable_interrupt();

    dma_set_reader_channel(line_length, line_count, 0);
    dma_set_writer_channel(line_length, line_count, 0);
    dma_set_both_start();
    wait_reader_irq();
    wait_writer_irq();

    wait_decode_irq();

    uint16_t width = jpeg_size_width();
    uint16_t height = jpeg_size_height();
    uint32_t bgr_filesize = 3 * width * height;

    if (cmpbuf(pSocAxilOutBuffer, pGoldenImage, bgr_filesize)) {
        printf("\nError while compare decoded BGR with GOLDEN one\n");
        return ++rc;
    }

    return rc;
}
