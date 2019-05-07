# spoke / test suite
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
  $ spoke test/bin/test_add.bin -t -d 2> replay_trace.tr 1> readable_trace.tr
```
##### Trace Decomposition
###### format break down
###### Numbers are all in hex
PC|write to register ?| rd address| rd value | read rs1 ?| rs1 address | rs1 value | read rs2 ? | rs2 address | rs2 value | read imm ? | imm val | mem access ? | load or store ? | mem address| mem value|flags

---|---| ---| --- | --- | --- | --- | --- | --- | ---| --- | ---| --- | --- |---| ---|---
4bits|1 bit|4 bits| 4 bits| 1 bit | 4 bits | 4 bits | 1 bit | 4 bits | 4 bits| 1 bit | 4 bits | 1 bit | 1 bit | 4 bits | 4 bits | 4 bits