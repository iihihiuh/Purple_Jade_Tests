# spoke / test suite
## General
##### This project contains an ARMv6-M Thumb Instruction Simulator `Spoke` and corresponding tests.
#### 1. Spoke
##### Spoke is an ARMv6-M Thumb Instruction Simulator, which reads in instruction streams and outputs expected outputs for every instructions. Every hardware implementations of ARMv6-M Thumb ISA should be able to produce the exact same output of this simulator to be deemed as correct.
#### 2. Test Suite
##### This project also contains assembly tests to verify correctness of hardware implementations of ARMv6-M Thumb ISA. Moreover, it also provides many untility functions in C++, which make contributing to this test suite eaiser.
##### It is highly encouraged to contribute to this test suite. As more tests are added, hardware tested by this test suite will become more robust.
#### 3. Additonal Supported instructions
##### In addition to required instructions by class. This simulator extends support for unsigned multiplication and divison.
Binary Encoding|Flag|ASM|Description
---|---|---|---
0100000101 rm(3 bits) rd (3 bits)| - | MULU Rd, Rd, Rn | Rd = $unsigned(Rd) * $unsigned(Rn)
0100000110 rm(3 bits) rd (3 bits)| - | DIVU Rd, Rd, Rn | Rd = $unsigned(Rd) / $unsigned(Rn)
##### Exceptions are not raised during if divided by zero.
## Folder directory

## Build
##### To Generate Tests run:
```
  $ make
```
##### Assembly code will be in `test/asm`. Compiled machine code will be in `test/bin`.
## Usage
#### Export Path
```
  $ export PATH=/the/absolute/path/to/Purple_Jade_Tests/spoke:${PATH}
```
#### Run
##### spoke
```
  $ spoke <test.bin> [options]
```
##### Options:
`-t` enable `spoke` to print traces to standard error

`-d` enable `spoke` to print human readable traces to standard output
##### example
```
  $ spoke test/bin/test_add.bin -t 2> replay_trace.tr > readable_trace.tr
```
##### Trace Decomposition
###### format break down
###### Numbers are all in hex
PC|write to register ?| rd address| rd value | read rs1 ?| rs1 address | rs1 value | read rs2 ? | rs2 address | rs2 value | read imm ? | imm val | mem access ? | load or store ? | mem address| mem value|flags
---|---| ---| --- | --- | --- | --- | --- | --- | ---| --- | ---| --- | --- |---| ---|---
4bits|1 bit|4 bits| 4 bits| 1 bit | 4 bits | 4 bits | 1 bit | 4 bits | 4 bits| 1 bit | 4 bits | 1 bit | 1 bit | 4 bits | 4 bits | 4 bits

## How to extend simulator to customized instructions

## How to contribute tests