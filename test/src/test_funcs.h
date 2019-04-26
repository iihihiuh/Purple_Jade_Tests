#ifndef _TEST_FUNCS_H_
#define _TEST_FUNCS_H_

#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

typedef uint16_t reg_t;

#define t0 7  // reserve register 0 as temporary register
#define t1 6

// inserting nops
void test_insert_nops(int n, ostream& s = cout, bool is_real_noop=false) {
	for (int i = 0; i < n; i++)
		if (!is_real_noop)
			s << "ADDS r7, r7, 0" << endl;
		else
			s << "NOOP" << endl;
}

// load immediates
void li(reg_t reg, reg_t val, ostream& s = cout) {
	s << "MOVS r" <<  t0 << ", " << (val >> 8) << endl;
	s << "MOVS r" <<  reg << ", " << 8 << endl;
	s << "LSLS r" <<  t0 << ", r" << t0 << ", r" << reg << endl;
	s << "MOVS r" << reg << ", " << (val & 0xff) << endl;
	s << "ORRS r" << reg << ", r" << t0 << endl;
}


// result comparasion
void test_cmp(reg_t dest, reg_t correctVal, ostream& s = cout) {
	li(t1, correctVal, s);
	s << "CMP r" << t1 << ", r" << dest << endl;
}

// tests for register-register operands
void test_rr_op(string inst, reg_t res, reg_t val1, reg_t val2,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	li(1, val1, s);
	li(2, val2, s);
	s << inst << ((is_shift | is_logic)? " r1, " : " r5, ") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	test_cmp(((is_shift | is_logic)? 1 : 5), res, s);
}

// eq scr dest
void test_rr_rs1_eq_dest(string inst, reg_t res, reg_t val1, reg_t val2,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	li(1, val1, s);
	li(2, val2, s);
	s << inst << ((is_shift | is_logic)? " r1, " : " r1, ") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	test_cmp(1, res, s);
}

void test_rr_rs2_eq_dest(string inst, reg_t res, reg_t val1, reg_t val2,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	li(1, val1, s);
	li(2, val2, s);
	s << inst << ((is_shift | is_logic)? " r1, " : " r2, ") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	test_cmp(((is_shift | is_logic)? 1 : 2), res, s);
}

void test_rr_rs1_eq_rs2(string inst, reg_t res, reg_t val1,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	li(1, val1, s);
	s << inst << ((is_shift | is_logic)? " r1, " : " r5,") << ((is_logic) ? "" :  " r1,") << " r1" << endl;
	test_cmp(((is_shift | is_logic)? 1 : 5), res, s);
}

void test_rr_dest_bypass(int num, int cycles, string inst, reg_t res, reg_t val1, reg_t val2,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	s << "MOVS r4, 0" << endl;
	s << "BYPASS" << num << ": ";
	li(1, val1, s);
	li(2, val2, s);
	s << inst << ((is_shift | is_logic)? " r1," : " r5,") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	test_insert_nops(cycles, s);
	s << "ADDS r3," << ((is_shift | is_logic)? " r1," : " r5,") <<" 0" << endl;
	s << "ADDS r4, r4, 1" << endl;
	s << "MOVS r0, 2" << endl;
	s << "CMP r0, r4" << endl;
	s << "BNE BYPASS" << num << endl;
	s << "NOOP" << endl;
	test_cmp(3 , res, s);
}

void test_rr_rs12_bypass(int num, int rs1_cycles, int rs2_cycles, string inst, reg_t res, reg_t val1, reg_t val2,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	s << "MOVS r4, 0" << endl;
	s << "BYPASS" << num << ": ";
	li(1, val1, s);
	test_insert_nops(rs1_cycles, s);
	li(2, val2, s);
	test_insert_nops(rs2_cycles, s);
	s << inst << ((is_shift | is_logic)? " r1, " : " r5,") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	s << "ADDS r4, r4, 1" << endl;
	s << "MOVS r0, 2" << endl;
	s << "CMP r0, r4" << endl;
	s << "BNE BYPASS" << num << endl;
	s << "NOOP" << endl;
	test_cmp(((is_shift | is_logic)? 1 : 5), res, s);
}

void test_rr_rs21_bypass(int num, int rs1_cycles, int rs2_cycles, string inst, reg_t res, reg_t val1, reg_t val2,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	s << "MOVS r4, 0" << endl;
	s << "BYPASS" << num << ": ";
	li(2, val2, s);
	test_insert_nops(rs2_cycles, s);
	li(1, val1, s);
	test_insert_nops(rs1_cycles, s);
	s << inst << ((is_shift | is_logic)? " r1, " : " r5,") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	s << "ADDS r4, r4, 1" << endl;
	s << "MOVS r0, 2" << endl;
	s << "CMP r0, r4" << endl;
	s << "BNE BYPASS" << num << endl;
	s << "NOOP" << endl;
	test_cmp(((is_shift | is_logic)? 1 : 5), res, s);
}

void test_ld_st_op(reg_t res, reg_t base, int cycles, reg_t offset, ostream& s=cout) {
	li(0, base, s); // loading base
	li(1, res, s);
	s << "STR r1, [r0, " << offset << "]" << endl;
	test_insert_nops(cycles, s);
	s << "LDR r5, [r0, " << offset << "]" << endl;
	test_cmp(5 , res, s);
}

void test_ld_st_bypass(int num, int rs1_cycles, int dest_cycles, reg_t res, reg_t base, int cycles, reg_t offset, bool st, ostream& s=cout) {
	s << "MOVS r4, 0" << endl;
	s << "BYPASS" << num << ": ";
	// st and ld
	if (st) {
		li(0, base, s); // loading base
		li(1, res, s);
	} else {
		li(1, res, s);
		li(0, base, s); // loading base
	}
	test_insert_nops(rs1_cycles, s);
	s << "STR r1, [r0, " << offset << "]" << endl;
	test_insert_nops(cycles, s);
	if (rs1_cycles > 0)
		li(0, base, s);
	test_insert_nops(rs1_cycles, s);
	s << "LDR r5, [r0, " << offset << "]" << endl;
	test_insert_nops(dest_cycles, s);
	s << "ADDS r3, r5, 0" << endl;
	s << "ADDS r4, r4, 1" << endl;
	s << "MOVS r0, 2" << endl;
	s << "CMP r0, r4" << endl;
	s << "BNE BYPASS" << num << endl;
	s << "NOOP" << endl;
	test_cmp(3 , res, s);
}

void test_rimm_op(reg_t res, string inst, reg_t val1, reg_t imm, bool is_sp=false, ostream& s=cout) {
	li(1, val1, s);
	s << inst << ((is_sp)? " SP," : " r5, ") << ((is_sp) ? " SP," :  " r1, ") << imm << endl;
	test_cmp(5 , res, s);
}

void test_rimm_eq_dst(reg_t res, string inst, reg_t val1, reg_t imm, bool is_sp=false, ostream& s=cout) {
	li(5, val1, s);
	s << inst << ((is_sp)? " SP," : " r5, ") << ((is_sp) ? " SP, " :  " r5, ") << imm << endl;
	test_cmp(5 , res, s);
}

void test_rimm_bypass(int num, int rs1_cycles, int dest_cycles, reg_t res, string inst,
	reg_t val1, reg_t imm, bool is_sp=false, ostream& s=cout) {
	s << "MOVS r4, 0" << endl;
	s << "BYPASS" << num << ": ";
	li(1, val1, s);
	test_insert_nops(rs1_cycles, s);
	s << inst << ((is_sp)? " SP," : " r5, ") << ((is_sp) ? " SP," :  " r1, ") << imm << endl;
	test_insert_nops(dest_cycles, s);
	s << "ADDS r3, r5, 0" << endl;
	s << "ADDS r4, r4, 1" << endl;
	s << "MOVS r0, 2" << endl;
	s << "CMP r0, r4" << endl;
	s << "BNE BYPASS" << num << endl;
	s << "NOOP" << endl;
	test_cmp(3 , res, s);
}

void dead_loop(int num, ostream& s=cout) {
	s << "DEAD" << num << ": B DEAD" << num << endl;
	s << "NOOP" << endl;
}

void test_bcond_taken(int num, int cycles, string cond, reg_t val1, reg_t val2, ostream& s=cout) {
	li(0, val1, s);
	li(1, val2, s);
	s << "CMP r0, r1" << endl;
	test_insert_nops(cycles, s, true);
	s << "B" << cond << " BYPASS" << num << endl;
	s << "NOOP" << endl;
	dead_loop(num, s);
	s << "BYPASS" << num << ": NOOP" << endl;
}

void test_bcond_not_taken(int num, int cycles, string cond, reg_t val1, reg_t val2, ostream& s=cout) {
	li(0, val1, s);
	li(1, val2, s);
	s << "CMP r0, r1" << endl;
	test_insert_nops(cycles, s, true);
	s << "B" << cond << " DEAD" << num << endl;
	s << "NOOP" << endl;
	s << "B " << " BYPASS" << num << endl;
	dead_loop(num, s);
	s << "BYPASS" << num << ": NOOP" << endl;
}
#endif  // header _TEST_FUNC_H_