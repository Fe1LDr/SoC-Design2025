// macros for bit manip
#define MAKE_FIELD(input,reg,field,value) ((input & ~(((1 << reg##_##field##_Size) - 1) << reg##_##field##_Offset)) \
 | ((value & ((1 << reg##_##field##_Size) - 1)) << reg##_##field##_Offset))

#define GET_FIELD(input,reg,field)        ((input >> reg##_##field##_Offset) & ((1 << reg##_##field##_Size) - 1))

#define BIT_ONE(reg, field)               (1 << reg##_##field##_Offset)
#define BIT_ZERO(reg, field)              (~(1 << reg##_##field##_Offset))

// dma registers
#define DMA_CONTROL 0x00
#define DMA_CONTROL_DefaultValue            0x00
#define DMA_CONTROL_Mask                    0xFFFFFFFF

#define DMA_CONTROL_WR_START_Size           1
#define DMA_CONTROL_WR_START_Offset         0

#define DMA_CONTROL_RD_START_Size           1
#define DMA_CONTROL_RD_START_Offset         1

#define DMA_CONTROL_WR_SYNCOFF_Size         1
#define DMA_CONTROL_WR_SYNCOFF_Offset       2

#define DMA_CONTROL_RD_SYNCOFF_Size         1
#define DMA_CONTROL_RD_SYNCOFF_Offset       3

#define DMA_CONTROL_WR_LOOP_Size            1
#define DMA_CONTROL_WR_LOOP_Offset          4

#define DMA_CONTROL_RD_LOOP_Size            1
#define DMA_CONTROL_RD_LOOP_Offset          5

#define DMA_STATUS 0x04
#define DMA_STATUS_DefaultValue             0x00
#define DMA_STATUS_Mask                     0x00000000
#define DMA_STATUS_WR_BUSY_Size             1
#define DMA_STATUS_WR_BUSY_Offset           0

#define DMA_STATUS_RD_BUSY_Size             1
#define DMA_STATUS_RD_BUSY_Offset           1

#define DMA_INTERRUPT_MASK 0x08
#define DMA_INTERRUPT_MASK_DefaultValue         0x00
#define DMA_INTERRUPT_MASK_Mask                 0xFFFFFFFF
#define DMA_INTERRUPT_MASK_WR_MASK_Size         1
#define DMA_INTERRUPT_MASK_WR_MASK_Offset       0

#define DMA_INTERRUPT_MASK_RD_MASK_Size         1
#define DMA_INTERRUPT_MASK_RD_MASK_Offset       1

#define DMA_INTERRUPT_STATUS 0x0C
#define DMA_INTERRUPT_STATUS_DefaultValue               0x00
#define DMA_INTERRUPT_STATUS_Mask                       0x00000000

#define DMA_INTERRUPT_STATUS_WR_INTERRUPT_Size          1
#define DMA_INTERRUPT_STATUS_WR_INTERRUPT_Offset        0

#define DMA_INTERRUPT_STATUS_RD_INTERRUPT_Size          1
#define DMA_INTERRUPT_STATUS_RD_INTERRUPT_Offset        1

#define DMA_READER_START_ADDRESS 0x10
#define DMA_READER_START_ADDRESS_DefaultValue   0x00
#define DMA_READER_START_ADDRESS_Mask           0xFFFFFFFF
#define DMA_READER_START_ADDRESS_Size           32
#define DMA_READER_START_ADDRESS_Offset         0

#define DMA_READER_LINE_LENGTH 0x14
#define DMA_READER_LINE_LENGTH_DefaultValue     0x00
#define DMA_READER_LINE_LENGTH_Mask             0xFFFFFFFF
#define DMA_READER_LINE_LENGTH_Size             32
#define DMA_READER_LINE_LENGTH_Offset           0

#define DMA_READER_LINE_COUNT 0x18
#define DMA_READER_LINE_COUNT_DefaultValue      0x00
#define DMA_READER_LINE_COUNT_Mask              0xFFFFFFFF
#define DMA_READER_LINE_COUNT_Size              32
#define DMA_READER_LINE_COUNT_Offset            0

#define DMA_READER_STRIDE 0x1C
#define DMA_READER_STRIDE_DefaultValue          0x00
#define DMA_READER_STRIDE_Mask                  0xFFFFFFFF
#define DMA_READER_STRIDE_Size                  32
#define DMA_READER_STRIDE_Offset                0

#define DMA_WRITER_START_ADDRESS 0x20
#define DMA_WRITER_START_ADDRESS_DefaultValue   0x00
#define DMA_WRITER_START_ADDRESS_Mask           0xFFFFFFFF
#define DMA_WRITER_START_ADDRESS_Size           32
#define DMA_WRITER_START_ADDRESS_Offset         0

#define DMA_WRITER_LINE_LENGTH 0x24
#define DMA_WRITER_LINE_LENGTH_DefaultValue     0x00
#define DMA_WRITER_LINE_LENGTH_Mask             0xFFFFFFFF
#define DMA_WRITER_LINE_LENGTH_Size             32
#define DMA_WRITER_LINE_LENGTH_Offset           0

#define DMA_WRITER_LINE_COUNT 0x28
#define DMA_WRITER_LINE_COUNT_DefaultValue      0x00
#define DMA_WRITER_LINE_COUNT_Mask              0xFFFFFFFF
#define DMA_WRITER_LINE_COUNT_Size              32
#define DMA_WRITER_LINE_COUNT_Offset            0

#define DMA_WRITER_STRIDE 0x2C
#define DMA_WRITER_STRIDE_DefaultValue          0x00
#define DMA_WRITER_STRIDE_Mask                  0xFFFFFFFF
#define DMA_WRITER_STRIDE_Size                  32
#define DMA_WRITER_STRIDE_Offset                0

#define DMA_VERSION 0x30
#define DMA_VERSION_DefaultValue                0x01
#define DMA_VERSION_Mask                        0x00000000
#define DMA_VERSION_Size                        32
#define DMA_VERSION_Offset                      0

#define DMA_CONFIGURATION 0x34
#define DMA_CONFIGURATION_DefaultValue          0x12
#define DMA_CONFIGURATION_Mask                  0x00000000
#define DMA_CONFIGURATION_Size                  32
#define DMA_CONFIGURATION_Offset                0

// decoder JPEG
#define JPEG_STATUS 0x00
#define JPEG_STATUS_DefaultValue                0x80000001
#define JPEG_STATUS_Mask                        0x80000000
#define JPEG_STATUS_IDLE_Size                   1
#define JPEG_STATUS_IDLE_Offset                 0

#define JPEG_STATUS_PROGRESSIVE_Size            1
#define JPEG_STATUS_PROGRESSIVE_Offset          8

#define JPEG_STATUS_RESET_Size                  1
#define JPEG_STATUS_RESET_Offset                31

#define JPEG_SIZE 0x04
#define JPEG_SIZE_DefaultValue                  0x00
#define JPEG_SIZE_Mask                          0x00000000
#define JPEG_SIZE_WIDTH_Size                    16
#define JPEG_SIZE_WIDTH_Offset                  0

#define JPEG_SIZE_HEIGHT_Size                   16
#define JPEG_SIZE_HEIGHT_Offset                 16

#define JPEG_PIXEL_COUNT 0x08
#define JPEG_PIXEL_COUNT_DefaultValue           0x00
#define JPEG_PIXEL_COUNT_Mask                   0x00000000
#define JPEG_PIXEL_COUNT_X_Size                 16
#define JPEG_PIXEL_COUNT_X_Offset               0

#define JPEG_PIXEL_COUNT_Y_Size                 16
#define JPEG_PIXEL_COUNT_Y_Offset               16

#define JPEG_VERSION 0x10
#define JPEG_VERSION_DefaultValue               0x42
#define JPEG_VERSION_Mask                       0x00000000
#define JPEG_VERSION_Size                       32
#define JPEG_VERSION_Offset                     0

#define JPEG_BASE_ADDRESS 0x14
#define JPEG_BASE_ADDRESS_DefaultValue          0
#define JPEG_BASE_ADDRESS_Mask                  0xFFFFFFFF
#define JPEG_BASE_ADDRESS_Size                  32
#define JPEG_BASE_ADDRESS_Offset                0