#pragma once
#include <inttypes.h>
#include <regs_defines.h>

enum DmaIrqMaskRegOptions {
    kWriterIrqEn = 0,
    kReaderIrqEn = 1
};

enum DmaControlRegOptions {
    kWriterStart        = 1 << 0,
    kReaderStart        = 1 << 1,
    kWriterSyncDisable  = 1 << 2,
    kReaderSyncDisable  = 1 << 3
};

enum JpegStatusRegOptions {
    kResetSet           = 1 << 31,
    kResetUnset         = 0
};

typedef struct {
    uint32_t addr;
    uint32_t line_len;
    uint32_t line_cnt;
    uint32_t stride;
} channel_regs;

typedef struct {
    uint32_t control_reg;
    uint32_t status_reg;
    uint32_t irq_mask_reg;
    uint32_t irq_status_reg;
    channel_regs reader;
    channel_regs writer;
    uint32_t version_reg;
    uint32_t config_reg;
} dma_t;

#define dma ((dma_t*)0x28000000)

typedef struct {
    uint32_t status_reg;
    uint32_t size_reg;
    uint32_t pixel_cnt_reg;
    uint32_t __reserved;
    uint32_t version_reg;
    uint32_t base_addr_reg;
} jpeg_decoder_t;

#define jpeg_decoder ((jpeg_decoder_t*)0x28001000)
