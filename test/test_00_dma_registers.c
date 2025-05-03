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
    if (test_default(&dma->control_reg, "DMA CONTROL", DMA_CONTROL_DefaultValue))
        rc = 1;
    if (test_default(&dma->status_reg, "DMA STATUS", DMA_STATUS_DefaultValue))
        rc = 1;
    if (test_default(&dma->irq_mask_reg, "DMA INTERRUPT MASK", DMA_INTERRUPT_MASK_DefaultValue))
        rc = 1;
    if (test_default(&dma->irq_status_reg, "DMA INTERRUPT STATUS", DMA_INTERRUPT_STATUS_DefaultValue))
        rc = 1;
    if (test_default(&dma->reader.addr, "DMA RD START ADDR", DMA_READER_START_ADDRESS_DefaultValue))
        rc = 1;
    if (test_default(&dma->reader.line_len, "DMA RD LINE LENGTH", DMA_READER_LINE_LENGTH_DefaultValue))
        rc = 1;
    if (test_default(&dma->reader.line_cnt, "DMA RD LINE COUNT", DMA_READER_LINE_COUNT_DefaultValue))
        rc = 1;
    if (test_default(&dma->reader.stride, "DMA RD STRIDE", DMA_READER_STRIDE_DefaultValue))
        rc = 1;
    if (test_default(&dma->writer.addr, "DMA WR START ADDR", DMA_WRITER_START_ADDRESS_DefaultValue))
        rc = 1;
    if (test_default(&dma->writer.line_len, "DMA WR LINE LENGTH", DMA_WRITER_LINE_LENGTH_DefaultValue))
        rc = 1;
    if (test_default(&dma->writer.line_cnt, "DMA WR LINE COUNT", DMA_WRITER_LINE_COUNT_DefaultValue))
        rc = 1;
    if (test_default(&dma->writer.stride, "DMA WR STRIDE", DMA_WRITER_STRIDE_DefaultValue))
        rc = 1;
    if (test_default(&dma->version_reg, "DMA VERSION", DMA_VERSION_DefaultValue))
        rc = 1;
    if (test_default(&dma->config_reg, "DMA CONFIGURATION", DMA_CONFIGURATION_DefaultValue))
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
    if (write_read(&dma->control_reg, "DMA CONTROL", DMA_CONTROL_Mask))
        rc = 1;
    if (write_read(&dma->status_reg, "DMA STATUS", DMA_STATUS_Mask))
        rc = 1;
    if (write_read(&dma->irq_mask_reg, "DMA INTERRUPT MASK", DMA_INTERRUPT_MASK_Mask))
        rc = 1;
    if (write_read(&dma->irq_status_reg, "DMA INTERRUPT STATUS", DMA_INTERRUPT_STATUS_Mask))
        rc = 1;
    if (write_read(&dma->reader.addr, "DMA RD START ADDR", DMA_READER_START_ADDRESS_Mask))
        rc = 1;
    if (write_read(&dma->reader.line_len, "DMA RD LINE LENGTH", DMA_READER_LINE_LENGTH_Mask))
        rc = 1;
    if (write_read(&dma->reader.line_cnt, "DMA RD LINE COUNT", DMA_READER_LINE_COUNT_Mask))
        rc = 1;
    if (write_read(&dma->reader.stride, "DMA RD STRIDE", DMA_READER_STRIDE_Mask))
        rc = 1;
    if (write_read(&dma->writer.addr, "DMA WR START ADDR", DMA_WRITER_START_ADDRESS_Mask))
        rc = 1;
    if (write_read(&dma->writer.line_len, "DMA WR LINE LENGTH", DMA_WRITER_LINE_LENGTH_Mask))
        rc = 1;
    if (write_read(&dma->writer.line_cnt, "DMA WR LINE COUNT", DMA_WRITER_LINE_COUNT_Mask))
        rc = 1;
    if (write_read(&dma->writer.stride, "DMA WR STRIDE", DMA_WRITER_STRIDE_Mask))
        rc = 1;
    if (write_read(&dma->version_reg, "DMA VERSION", DMA_VERSION_Mask))
        rc = 1;
    if (write_read(&dma->config_reg, "DMA CONFIGURATION", DMA_CONFIGURATION_Mask))
        rc = 1;
    return rc;
}

int sim_main() {
    printf("--- TEST ACCESS TO DMA REGISTERS ---\n");
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
