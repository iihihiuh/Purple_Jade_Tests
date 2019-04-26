TEST_TOP = $(shell pwd)
SPOKE_DIR = $(TEST_TOP)/src
ASM_DIR =  $(TEST_TOP)/test/asm
ASM_SRC_DIR =  $(TEST_TOP)/test/src
BIN_DIR = $(TEST_TOP)/test/bin

all: tests

tests:
	make -C $(SPOKE_DIR)
	make -C $(ASM_SRC_DIR)
	make -C $(ASM_DIR)
	if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi
	mv $(ASM_DIR)/test*.bin $(BIN_DIR)

clean:
	make -C $(SPOKE_DIR) clean
	make -C $(ASM_SRC_DIR) clean
	make -C $(ASM_DIR) clean
	rm -rf $(BIN_DIR)