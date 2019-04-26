# Assemble binary instruction files from the provided sources

.PHONY: clean

sources := $(shell ls *.asm)
objects := $(sources:%.asm=%.bin)

all: $(objects)

%.bin: %.asm
	python assemble.py $< > $@

clean:
	-rm -rf *.bin test_*.asm
