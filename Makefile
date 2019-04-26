TEST_TOP = $(shell pwd)
SPOKE_DIR = $(TEST_TOP)/src
ASM_DIR =  $(TEST_TOP)/test/asm
ASM_SRC_DIR =  $(TEST_TOP)/test/src

all: tests

tests:
	make -C $(SPOKE_DIR)
	make -C $(ASM_SRC_DIR)
	make -C $(ASM_DIR)

clean:
	make -C $(SPOKE_DIR) clean
	make -C $(ASM_SRC_DIR) clean
	make -C $(ASM_DIR) clean