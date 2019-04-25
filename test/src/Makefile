CC = g++
CFLG = -std=c++11 -Wall -g
MAINHEADERs = test_funcs.h
RM = rm -rf
SOURCES := $(shell ls *.cc)
FLD = ../asm/
OBJECTS := $(SOURCES:%.cc=$(FLD)%.asm)
JUNK = *.elf *.dSYM *.asm

all : $(OBJECTS)

%.asm : %.cc $(MAINHEADERs)
	$(CC) $(CFLG) $< -o $*.elf
	./$*.elf > $@

clean:
	$(RM) $(JUNK)