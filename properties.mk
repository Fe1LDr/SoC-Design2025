
GCC = riscv64-unknown-elf-gcc
AS = riscv64-unknown-elf-as
OBJCOPY = riscv64-unknown-elf-objcopy
LD = riscv64-unknown-elf-ld
XILINX_QEMU ?= /opt/qemu/build
QEMU = ${XILINX_QEMU}/qemu-system-riscv32
MPEG = ffmpeg

TARGET = $(TEST_NAME)_$(notdir $(IMAGE_NAME)).elf

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
TEST_OBJ_DIR = $(BUILD_DIR)/obj
IMG_BUILD_DIR = $(BUILD_DIR)/img
COVERAGE_DIR = $(BUILD_DIR)/sim
SOCKET_NAME ?= $(BUILD_DIR)/cosim.sock
SRC_DIR = src
ASM_DIR = asm
LD_DIR = ld
TEST_DIR = test
IMG_DIR = img
BGR_DIR = bgr
SIM_EXE = snapshot/design${DESIGN_NUM}/case${DESIGN_NUM}

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJ_SRCS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
ASMS := $(shell find $(ASM_DIR) -name '*.s')
OBJ_ASMS := $(ASMS:$(ASM_DIR)/%.s=$(OBJ_DIR)/%.o)
LDS := $(shell find $(LD_DIR) -name '*.ld')

MERGED_COVERAGE_FILE := $(COVERAGE_DIR)/merged.info
COVERAGE_FILE := $(COVERAGE_DIR)/lcov.info
ifeq ("$(wildcard $(MERGED_COVERAGE_FILE))","")
	COVERAGE_FILE := $(MERGED_COVERAGE_FILE)
else
	COVERAGE_FILE := $(COVERAGE_DIR)/lcov.info
endif

QEMU_FLAGS = -M virt-cosim -chardev socket,id=cosim,path=${SOCKET_NAME},server=on -nographic \
			 -machine-path ${BUILD_DIR}/machine-riscv64 -serial mon:stdio \
             -semihosting --semihosting-config enable=on,target=native \
			 -bios $(BUILD_DIR)/$(TARGET)
MPEG_FLAGS = -y -i $(IMG_DIR)/$(IMAGE_NAME).jpg -loglevel quiet
GCC_FLAGS = -c -g -O0 -Iinclude/ -ffreestanding -march=rv32imac_zicsr -mno-relax -mabi=ilp32
AS_FLAGS = -g -march=rv32imac_zicsr -mabi=ilp32
OBJCOPY_SECTION_FLAGS1 = --add-section .image=$(IMG_DIR)/$(IMAGE_NAME).jpg --set-section-flags .image=data,load,readonly
OBJCOPY_SECTION_FLAGS2 = --add-section .expected=$(IMG_BUILD_DIR)/$(IMAGE_NAME).$(IMAGE_FORMAT) --set-section-flags .expected=data,load,readonly
LD_FLAGS = -mno-relax -mabi=ilp32 -march=rv32imac_zicsr -specs=picolibc.specs --oslib=semihost -lc -lsemihost 
