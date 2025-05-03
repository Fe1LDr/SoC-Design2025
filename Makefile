TEST_NAME?=example_test
IMAGE_NAME?=example_image
IMAGE_FORMAT?=bmp
DESIGN_NUM?=0
TIMEOUT?=60
EXIT_CODE_FILE?=.exit_code

include properties.mk

.PHONY: all

all: build
	make -j2 run_all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(GCC) $(GCC_FLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(ASM_DIR)/%.s
	mkdir -p $(OBJ_DIR)
	$(AS) $(AS_FLAGS) -o $@ $<

$(OBJ_DIR)/$(TEST_NAME)_empty.o: $(TEST_DIR)/$(TEST_NAME).c
	mkdir -p $(OBJ_DIR)
	$(GCC) $(GCC_FLAGS) -o $@ -c $<

$(IMG_BUILD_DIR)/$(IMAGE_NAME).bmp: $(IMG_DIR)/$(IMAGE_NAME).jpg
	mkdir -p $(IMG_BUILD_DIR)
	$(MPEG) $(MPEG_FLAGS) $(IMG_BUILD_DIR)/$(IMAGE_NAME).bmp

$(IMG_BUILD_DIR)/$(IMAGE_NAME).bgr: $(BGR_DIR)/$(IMAGE_NAME).bgr
	mkdir -p $(IMG_BUILD_DIR)
	cp $(BGR_DIR)/$(IMAGE_NAME).bgr $(IMG_BUILD_DIR)/$(IMAGE_NAME).bgr

$(OBJ_DIR)/$(TARGET)_image.o: $(OBJ_DIR)/$(TEST_NAME)_empty.o $(IMG_DIR)/$(IMAGE_NAME).jpg
	mkdir -p $(TEST_OBJ_DIR)
	$(OBJCOPY) $(OBJCOPY_SECTION_FLAGS1) $(OBJ_DIR)/$(TEST_NAME)_empty.o $@

$(TEST_OBJ_DIR)/$(TARGET).o: $(OBJ_DIR)/$(TARGET)_image.o $(IMG_BUILD_DIR)/$(IMAGE_NAME).$(IMAGE_FORMAT)
	$(OBJCOPY) $(OBJCOPY_SECTION_FLAGS2) $(OBJ_DIR)/$(TARGET)_image.o $@

$(BUILD_DIR)/$(TARGET): $(OBJ_SRCS) $(OBJ_ASMS) $(TEST_OBJ_DIR)/$(TARGET).o
	$(GCC) $(LD_FLAGS) -T $(LDS) -o $@ $(OBJ_SRCS) $(OBJ_ASMS) $(TEST_OBJ_DIR)/$(TARGET).o
	
build: $(BUILD_DIR)/$(TARGET)

qemu: build
	$(QEMU) $(QEMU_FLAGS)

run_all: qemu simulator

simulator:
	sleep 2
	-timeout $(TIMEOUT)s ./$(SIM_EXE) ${SOCKET_NAME}; \
	EXIT_CODE=$$?; \
	echo $$EXIT_CODE; \
	if [ $$EXIT_CODE -ne 0 ]; then \
		echo $$EXIT_CODE > $(EXIT_CODE_FILE); \
    fi

coverage:
	mkdir -p $(COVERAGE_DIR)
	verilator_coverage coverage.dat --write-info $(COVERAGE_FILE)
	rm coverage.dat
	lcov -r $(COVERAGE_FILE) -o $(COVERAGE_FILE) '*testbench/*' '*aq_axis_djpeg*'
	lcov -a $(COVERAGE_FILE) -a $(MERGED_COVERAGE_FILE) -o $(MERGED_COVERAGE_FILE)

clean:
	rm -rf $(BUILD_DIR)