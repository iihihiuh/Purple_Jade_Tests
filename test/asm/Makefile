# Assemble binary instruction files from the provided sources

.PHONY: clean

sources := $(shell ls *.asm)
objects := $(sources:%.asm=%.bin)
noop := 0000000000000000

all: $(objects)

%.bin: %.asm
	python assemble.py $< > $@
	echo $(noop) >> $@
	echo $(noop) >> $@
	echo $(noop) >> $@
	echo $(noop) >> $@
	echo $(noop) >> $@
	echo $(noop) >> $@
	echo $(noop) >> $@
	echo $(noop) >> $@
	echo $(noop) >> $@
	echo $(noop) >> $@

clean:
	-rm -rf *.bin test_*.asm
