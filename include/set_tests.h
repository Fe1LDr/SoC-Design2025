#pragma once
#include <stdint.h>

void wait_reader_irq(void);
void wait_writer_irq(void);
void wait_decode_irq(void);

void dma_enable_interrupt(void);
void dma_set_reader_channel(uint32_t lineLength, uint32_t lineCount, uint32_t stride);
void dma_set_writer_channel(uint32_t lineLength, uint32_t lineCount, uint32_t stride);
void dma_set_reader_start(void);
void dma_set_writer_start(void);
void dma_set_both_start(void);
// wait while busy
void dma_wait_reader(void);
// wait while busy
void dma_wait_writer(void);

void jpeg_set_programm_reset(void);
void jpeg_setup_decoder(void);
void jpeg_wait_idle(void);
uint16_t jpeg_size_width(void);
uint16_t jpeg_size_height(void);
uint8_t jpeg_check_progressive(void);
