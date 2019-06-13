# spoke / test suite
## General
##### This project contains an ARMv6-M Thumb Instruction Simulator `Spoke` and corresponding tests.
#### 1. Spoke
Spoke is an ARMv6-M Thumb Instruction Simulator, which reads in instruction streams and outputs expected outputs for every instruction. Every hardware implementation of ARMv6-M Thumb ISA should be able to produce the exact same output of this simulator to be deemed as correct.
#### 2. Test Suite
This project also contains assembly tests to verify correctness of hardware implementations of ARMv6-M Thumb ISA. Moreover, it provides many utility functions in C++, which make contributing to this test suite easier.

It is highly encouraged to contribute to this test suite. As more tests are added, hardware tested by this test suite will become more robust.
#### 3. Additonal Supported instructions
In addition to required instructions by class. This simulator extends support for unsigned multiplication and division.

Binary Encoding|Flag|ASM|Description
---|---|---|---
0100000101 rm(3 bits) rd (3 bits)| Not Set | MULU Rd, Rd, Rn | Rd = $unsigned(Rd) * $unsigned(Rn)
0100000110 rm(3 bits) rd (3 bits)| Not Set | DIVU Rd, Rd, Rn | Rd = $unsigned(Rd) / $unsigned(Rn)
##### Note : Exceptions are not raised during division if divided by zero. Division by zero is essentially treated as noop by this simulator.
## Folder directory
Folder Name |Description
---|---
spoke|contains source files for simulator spoke
test/asm|contains some hand written asm tests
test/src|contains sources files to generate asm tests
test/bin|contains binary files generated by assembler
## Build
##### To Compile `spoke` and generate tests run:
```
  $ make
```
##### Compiled simulator will be in `spoke/spoke`. 
##### Generated assembly tests will be in `test/asm`. Compiled machine code will be in `test/bin`.
## Usage
#### Export Path
```
  $ export PATH=/the/absolute/path/to/Purple_Jade_Tests/spoke:${PATH}
```
This command will put the path to spoke to environmental variable PATH. It is highly recommended to append this line to `.bashrc` in home directory. Thus, `spoke` can be invoked by typing spoke in command line terminals.
#### Run `spoke`
```
  $ spoke <test.bin> [options]
```
##### Options:
`-t` enable `spoke` to print traces to standard error

`-d` enable `spoke` execute only one instruction when user type return in terminal
##### example
```
  $ spoke test/bin/test_add.bin -t 2> replay_trace.tr > readable_trace.tr
```
The command above will print human readable instructin execution trace to readable_trace.tr and replay_trace.tr will contain traces you will use for trace replay during verification process.
##### Note: `2>` <file_name> means write the standard error output of a program to a file and `>`  <file_name> means write the standard output of a program to a file
## Trace Decomposition
#### The default format of traces in trace_replay.tr is shown below.
Program Counter|is_reg_write| rd address| rd value |is_mem_write | mem address| mem value|current flags
---|---| ---| --- | --- | --- | --- | --- 
4 hex digits |1 hex digit|4 hex digits| 4 hex digits|1 hex digit|4 hex digits| 4 hex digits|1 hex digit
#### Flags are represented using a hex digit, its format is shown below
C|N|Z|V
---|---|---|--- 
4th bit|3rd bit|2nd bit|1st bit
#### examples:
#### This trace `00051000700f00000000000` means instruction at pc 0x0005 writes to register 7 a value of 0x00f0.
#### This trace `001c00000000010003fdf04` means instruction at pc 0x001c writes to memory 0x3 a value of 0xfdf0 and only N flag is set.
## Customized Trace
In file `spoke/trace.cc`, you can modify function `print_trace()` to change the trace format that fits you the best. There are many additional more information logged during instruction simulation that can be to into traces like memory read and immediates used. Please refer to `log_t` in `spoke/processor.h` for more information.
## How to extend simulator to customized instructions
### 1. Add instruction encoding information in `spoke/encoding.h`
Use macro `INSTR_MATCH` to define customized instruction encoding format. This macro is used to help you determined instruction types.
##### For example : MOVS is registered in `encoding.h` as `INSTR_MATCH(MOVS,0xF800,0x2000)`. Second argument of `INSTR_MATCH` is to mask out the digit you want to inspect and the third argument of `INSTR_MATCH` is actual encoding of your customized instruction. Use zero for do not care.
### 2. Add instrucion execution details in function `step(bool)` in file `spoke/processor.cc`
Add another `else if` block to the big `if statement`. Be sure to use utility functions in `spoke/processor.h` so that reads and writes to architectural states can be properly logged. Descriptions of helper utility functions are shown below.

Function Name|Description
---|---
get_bits(value,start,length)| grab bits value[start:start+len-1]
getReg(addr)| get given register value
setReg(addr,value)| set given register value
getMem(addr)| get memory value at given address
setMem(addr,value)| set given memory address to given value
log_imm(value) | If you are using imm in your instruction and you wish to use this imm in trace replay. Be sure to use this function to log imm used.
## How to contribute tests
###  1. Contribute hand written asm tests
Just put you asm file in `test/asm`. DO NOT use `test_` as your file prefix. This prefix is reserved for generated asm files, which are deleted during `make clean`.
### 2. Contribute tests using C++ untility functions
Put your C++ program in `test/src`. Be sure to use `test_` as your file prefix. You can use unitility functions in `test/src/test_func.h` to help you print asm, such as `li(reg,value)` which will print a series of assembly to load a given value to a given register.
