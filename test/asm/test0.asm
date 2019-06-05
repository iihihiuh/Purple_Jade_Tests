// Test ALU, Branch and BL

MOVS R2, 3      // 3 -> R2
MOV R6, R2      // 3 -> R6
ADDS R4, R2, 7  // 3+7 -> R4
ADDS R3, R4, R6 // 10+3 -> R3
SUBS R0, R6, R2 // 3-3 -> R0
SUBS R1, R2, 0  // 3-0 -> R1
CMP R4, R0      // 0==10 -> z_flag
ANDS R2, R6     // 0x0003 & 0x0003 -> R2
EORS R4, R0     // 0x000A ^ 0x0000 -> R4
ORRS R1, R3     // 0x0003 | 0x000D = 0x000F -> R1
MVNS R5, R0     // 0xFFFF -> R5
LSLS R1, R1, R5 // 0x8000 -> R1
LSRS R4, R4, R6 // 0x0001 -> R4
ASRS R5, R5, R3 // 0xFFFF -> R5
MULU R5, R5, R3
BL SKIP         // 20 -> PC, 16 -> LR
NOOP            // ...
STR R4, [R0, 9] // 0x0001 -> Mem[9]
LDR R7, [R0, 9] // R7 <- 0x0001
B END           // 23 -> PC
NOOP            // ..
SKIP: RORS R4, R4, R2 // 0x2000 -> R4
BX R14          // 16 -> PC
END: NOOP     // ..
