#include "boot.h"
#include "converter.h"
#include "irq.h"
#include "regs.h"
#include <stdio.h>
#include <stdlib.h>

#include "set_tests.h"

int test_default(uint32_t* reg_addr, char* reg_name, uint32_t exp_value) {
    int reg = read_mem_32(reg_addr);
    if (reg != exp_value) {
        printf("%s register default value not match\n", reg_name);
        printf("Actual: 0x%lx, Expected: 0x%lx\n", reg, exp_value);
        return 1;
    }
    return 0;
}

int test_checking_default_values() {
    int rc = 0;
    if (test_default(&jpeg_decoder->status_reg, "JPEG STATUS", JPEG_STATUS_DefaultValue))
        rc = 1;
    if (test_default(&jpeg_decoder->size_reg, "JPEG SIZE", JPEG_SIZE_DefaultValue))
        rc = 1;
    if (test_default(&jpeg_decoder->pixel_cnt_reg, "JPEG PIXEL COUNT", JPEG_PIXEL_COUNT_DefaultValue))
        rc = 1;
    if (test_default(&jpeg_decoder->version_reg, "JPEG VERSION", JPEG_VERSION_DefaultValue))
        rc = 1;
    if (test_default(&jpeg_decoder->base_addr_reg, "JPEG BASE ADDR", JPEG_BASE_ADDRESS_DefaultValue))
        rc = 1;
    return rc;
}

int sim_main() {
    int rc = 0;
    int line_length = 256;
    int line_count = kImageSize / line_length + 1;

    jpeg_setup_decoder();

    wfi_decode = true;

    dma_set_reader_channel(line_length, line_count, 0);
    dma_set_writer_channel(line_length, line_count, 0);
    // dont use lib function - manualy start and disable wr loop
    write_mem_32( &dma->control_reg, BIT_ONE(DMA_CONTROL, RD_LOOP) |
                                     BIT_ONE(DMA_CONTROL, RD_START)|
                                     BIT_ONE(DMA_CONTROL, WR_START));
    printf( "DMA reader & writer work start; loop enabled\n" );
    printf( "Not waiting to finish; setting reset when not idle\n" );
    while (read_mem_32(&jpeg_decoder->status_reg) & BIT_ONE(JPEG_STATUS, IDLE)) { }

    // set programm reset back
    jpeg_set_programm_reset();
    rc = test_checking_default_values();

    jpeg_setup_decoder();
    if (rc)
        return rc;

    return rc;
}
