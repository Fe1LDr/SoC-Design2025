#include "set_tests.h"
#include <stdint.h>
#include "regs.h"
#include "mem_access.h"
#include "boot.h"
#include "irq.h"

void wait_reader_irq(void) {
    printf("Start waiting for READER IRQ\n");
    while (wfi_reader) {}
    printf("Received. Living.\n");
}

void wait_writer_irq(void) {
    printf("Start waiting for WRITER IRQ\n");
    while (wfi_writer) {}
    printf("Received. Living.\n");
}

void wait_decode_irq(void) {
    printf("Start waiting for DECODE IRQ\n");
    while (wfi_decode) {}
    printf("Received. Living.\n");
}

// --------------------

void dma_enable_interrupt() {
    write_mem_32( &dma->irq_mask_reg, BIT_ONE(DMA_INTERRUPT_MASK, RD_MASK) |
                                      BIT_ONE(DMA_INTERRUPT_MASK, WR_MASK));
}

void dma_set_reader_channel(uint32_t lineLength, uint32_t lineCount, uint32_t stride) {
    write_mem_32( &dma->reader.addr, pJpegImage );	    //адрес начала картинки, которую надо передать
	write_mem_32( &dma->reader.line_len, lineLength );	//количество слов (по 4 байта) в транзакции
	write_mem_32( &dma->reader.line_cnt, lineCount );	//количество транзакций
    write_mem_32( &dma->reader.stride, stride );
}

void dma_set_writer_channel(uint32_t lineLength, uint32_t lineCount, uint32_t stride) {
    write_mem_32( &dma->writer.line_len, lineLength );	//количество слов (по 4 байта) в транзакции
	write_mem_32( &dma->writer.line_cnt, lineCount );	//количество транзакций
    write_mem_32( &dma->writer.stride, stride );
}

void dma_set_reader_start() {
    write_mem_32( &dma->control_reg, BIT_ONE(DMA_CONTROL, RD_LOOP) | 
                                     BIT_ONE(DMA_CONTROL, RD_START));
    printf( "DMA reader work start; loop enabled\n" );
}

void dma_set_writer_start() {
    write_mem_32( &dma->control_reg, BIT_ONE(DMA_CONTROL, WR_LOOP) | 
                                     BIT_ONE(DMA_CONTROL, WR_START) );
    printf( "DMA reader work start; loop enabled\n" );
}

void dma_set_both_start() {
    write_mem_32( &dma->control_reg, BIT_ONE(DMA_CONTROL, RD_LOOP) | 
                                     BIT_ONE(DMA_CONTROL, RD_START)|
                                     BIT_ONE(DMA_CONTROL, WR_LOOP) | 
                                     BIT_ONE(DMA_CONTROL, WR_START));
    printf( "DMA reader & writer work start; loop enabled\n" );
}

void dma_wait_reader() {
    while (read_mem_32(&dma->status_reg) & BIT_ONE(DMA_STATUS, RD_BUSY)) { };
    printf( "DMA reader work done;\n" );
}

void dma_wait_writer() {
    while (read_mem_32(&dma->status_reg) & BIT_ONE(DMA_STATUS, WR_BUSY)) { };
    printf( "DMA writer work done;\n" );
}

// --------------------

void jpeg_set_programm_reset() {
    write_mem_32( &jpeg_decoder->status_reg, BIT_ONE(JPEG_STATUS, RESET) );
}

void jpeg_setup_decoder() {
    write_mem_32( &jpeg_decoder->status_reg, BIT_ZERO(JPEG_STATUS, RESET) );
	write_mem_32( &jpeg_decoder->base_addr_reg, pSocAxilOutBuffer );
}

void jpeg_wait_idle() {
    while (read_mem_32(&jpeg_decoder->status_reg) & BIT_ZERO(JPEG_STATUS, IDLE)) { };
    printf( "JPEG Decoder end work; now in IDLE state;\n" );
}

uint16_t jpeg_size_width() {
    uint32_t reg = read_mem_32(&jpeg_decoder->size_reg);
    printf( "JPEG Size: width  0x%X;\n", reg & 0x0000FFFF);
    return reg & 0x0000FFFF;
}

uint16_t jpeg_size_height() {
    uint32_t reg = read_mem_32(&jpeg_decoder->size_reg);
    printf( "JPEG Size: height 0x%X\n", (reg >> 16));
    return (reg >> 16);
}

uint8_t jpeg_check_progressive() {
    uint32_t reg = read_mem_32(&jpeg_decoder->status_reg);
    printf( "JPEG progressive flag: %d;\n", reg && BIT_ONE(JPEG_STATUS, PROGRESSIVE));
    return reg && BIT_ONE(JPEG_STATUS, PROGRESSIVE);
}
