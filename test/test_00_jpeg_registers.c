#include "boot.h"
#include "converter.h"
#include "irq.h"
#include "regs.h"
#include <stdio.h>
#include <stdlib.h>

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

int write_read(uint32_t* reg_addr, char* reg_name, uint32_t mask) {
    // first write all 0`s
    int before = read_mem_32(reg_addr);
    int expected = 0;
    write_mem_32(reg_addr, expected);
    int after = read_mem_32(reg_addr);
    if (after != ((before & ~mask) | (expected & mask))) {
        printf("%s register value not match; write all 0`s\n", reg_name);
        printf("Actual: 0x%lx, Expected: 0x%lx\n", after, ((before & ~mask) | (expected & mask)));
        return 1;
    }
    // then write all 1`s
    before = read_mem_32(reg_addr);
    expected = 0xFFFFFFFF;
    write_mem_32(reg_addr, expected);
    after = read_mem_32(reg_addr);
    if (after != ((before & ~mask) | (expected & mask))) {
        printf("%s register value not match; write all 1`s\n", reg_name);
        printf("Actual: 0x%lx, Expected: 0x%lx\n", after, ((before & ~mask) | (expected & mask)));
        return 1;
    }
    return 0;
}

int test_writing_and_reading_regs() {
    int rc = 0;
    if (write_read(&jpeg_decoder->status_reg, "JPEG STATUS", JPEG_STATUS_Mask))
        rc = 1;
    if (write_read(&jpeg_decoder->size_reg, "JPEG SIZE", JPEG_SIZE_Mask))
        rc = 1;
    if (write_read(&jpeg_decoder->pixel_cnt_reg, "JPEG PIXEL COUNT", JPEG_PIXEL_COUNT_Mask))
        rc = 1;
    if (write_read(&jpeg_decoder->version_reg, "JPEG VERSION", JPEG_VERSION_Mask))
        rc = 1;
    // check base addr reg
    // write all 1`s
    write_mem_32(&jpeg_decoder->base_addr_reg, 0xFFFFFFFF);
    int after = read_mem_32(&jpeg_decoder->base_addr_reg);
    if (after != 0x00000000) {
        printf("JPEG BASE ADDR register value not match; write all 1`s\n");
        printf("Actual: 0x%lx, Expected: 0x%lx\n", after, 0x00000000);
        rc = 1;
    }
    return rc;
}

int sim_main() {
    printf("--- TEST ACCESS TO JPEG REGISTERS ---\n");
    int rc = 0;
    rc |= test_checking_default_values();
    rc |= test_writing_and_reading_regs();
    if (rc) {
        printf("--- TEST FAILED ---\n");
    } else {
        printf("--- TEST PASSED ---\n");
    }
    return rc;
}
