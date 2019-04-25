CC = g++
CFLG = -std=c++11 -Wall -g
MAINHEADERs = test_funcs.h
RM = rm -rf
SOURCES := $(shell ls *.cc)
OBJECTS := $(SOURCES:%.cc=%.asm)
FLD = ../asm/
JUNK = *.elf *.dSYM *.asm

all : $(OBJECTS)

%.asm : %.cc $(MAINHEADERs)
	$(CC) $(CFLG) $< -o $*.elf
	./$*.elf > $(FLD)$@

clean:
	$(RM) $(JUNK)