#include "boot.h"
#include "converter.h"
#include "irq.h"
#include "regs.h"
#include <stdio.h>
#include <stdlib.h>

#include "set_tests.h"

int sim_main() {
    int rc = 0;
    int line_length = 4;
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

    return rc;
}
