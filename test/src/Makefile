CC = g++
CFLG = -std=c++11 -Wall -g
MAINHEADERs = test_funcs.h
RM = rm -rf
SOURCES := $(shell ls *.cc)
FLD = ../asm/
OBJECTS := $(SOURCES:%.cc=$(FLD)%.asm)
JUNK = *.elf *.dSYM *.asm

all : $(OBJECTS)

$(FLD)%.asm : %.cc $(MAINHEADERs)
	$(CC) $(CFLG) $< -o $*.elf
	./$*.elf > $@
	$(RM) $*.elf $*.elf.dSYM

clean:
	$(RM) $(JUNK)