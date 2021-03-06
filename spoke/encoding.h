#ifndef _ENCODING_H_
#define _ENCODING_H_

#include <cstdint>

typedef uint16_t Instr;

#define INSTR_MATCH(name,mask,match) \
	inline bool match_##name(Instr ins) { \
		return ! ((ins & mask) ^  match); \
	}

INSTR_MATCH(MOVS,0xF800,0x2000)
INSTR_MATCH(MOV,0xFF80,0x4600)
INSTR_MATCH(ADDIMM,0xFE00,0x1c00)
INSTR_MATCH(ADDREG,0xFE00,0x1800)
INSTR_MATCH(ADDSP,0xFF80,0xB000)
INSTR_MATCH(SUBREG,0xFE00,0x1A00)
INSTR_MATCH(SUBIMM,0xFE00,0x1E00)
INSTR_MATCH(SUBSP,0xFF80,0xB080)
INSTR_MATCH(CMP,0xFFC0,0x4280)
INSTR_MATCH(AND,0xFFC0,0x4000)
INSTR_MATCH(EOR,0xFFC0,0x4040)
INSTR_MATCH(OR,0xFFC0,0x4300)
INSTR_MATCH(MVNS,0xFFC0,0x43c0)
INSTR_MATCH(LSLS,0xFFC0,0x4080)
INSTR_MATCH(LSRS,0xFFC0,0x40c0)
INSTR_MATCH(ASRS,0xFFC0,0x4100)
INSTR_MATCH(RORS,0xFFC0,0x41c0)
INSTR_MATCH(MULU,0xFFC0,0x4140)
INSTR_MATCH(DIVU,0xFFC0,0x4180)
INSTR_MATCH(ST,0xF800,0x6000)
INSTR_MATCH(LD,0xF800,0x6800)
INSTR_MATCH(B,0xF800,0xE000)
INSTR_MATCH(BL,0xFFC0,0x4500)
INSTR_MATCH(BX,0xFF87,0x4700)
INSTR_MATCH(BCOND,0xF000,0xD000)
INSTR_MATCH(NOOP,0xFFFF,0xBF00)
// define additional instruction here
// INSTR_MATCH(instruction_name,instruction,instruction_mask,instruction_match)
// this macro is used to help you determined type of instructions. 
// eg : instruction movs is 0b00101xxxxxxxxxxx
//      instruction mask for movs will be 0b1111100000000000 -> 0xF800
//      instruction match for movs will be 0b0010100000000000 -> 0x2000


#define EQ 0x0
#define NE 0x1
#define CS 0x2
#define CC 0x3
#define MI 0x4
#define PL 0x5
#define VS 0x6
#define VC 0x7
#define HI 0x8
#define LS 0x9
#define GE 0xA
#define LT 0xB
#define GT 0xC
#define LE 0xD
#define AL 0xE

#endif