// Test the store and load instructions

// Register-imm MOV
MOVS R0, 1
MOVS R1, 2
MOVS R2, 4
MOVS R3, 8
MOVS R4, 16
MOVS R5, 32
MOVS R6, 64
MOVS R7, 128
// 128 -> Mem[2]
STR R7, [R0, 1]
// 64 -> Mem[4]
STR R6, [R1, 2]
// 32 -> Mem[20]
STR R5, [R2, 16]
// 16 -> Mem[39]
STR R4, [R3, 31]
// R3 <- Mem[39]==16
LDR R3, [R3, 31]
// R2 <- Mem[20]==32
LDR R2, [R2, 16]
// R1 <- Mem[4]==64
LDR R1, [R1, 2]
// R0 <- Mem[2]==128
LDR R0, [R0, 1]
