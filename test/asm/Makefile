# Assemble binary instruction files from the provided sources

.PHONY: clean

sources := test0.asm test1.asm test2.asm
objects := $(sources:%.asm=%.bin)

all: $(objects)

%.bin: %.asm
	python assemble.py $< > $@

clean:
	-rm -rf *.bin
