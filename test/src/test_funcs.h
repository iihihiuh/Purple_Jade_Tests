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
void test_insert_nops(int n, ostream& s = cout) {
	for (int i = 0; i < n; i++)
		s << "ADDS r7, r7, 0" << endl;
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
	test_cmp(5 , res, s);
}

// eq scr dest
void test_rr_rs1_eq_dest(string inst, reg_t res, reg_t val1, reg_t val2,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	li(1, val1, s);
	li(2, val2, s);
	s << inst << ((is_shift | is_logic)? " r1, " : " r1, ") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	test_cmp(1 , res, s);
}

void test_rr_rs2_eq_dest(string inst, reg_t res, reg_t val1, reg_t val2,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	li(1, val1, s);
	li(2, val2, s);
	s << inst << ((is_shift | is_logic)? " r1, " : " r2, ") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	test_cmp(2 , res, s);
}

void test_rr_rs1_eq_rs2(string inst, reg_t res, reg_t val1,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	li(1, val1, s);
	s << inst << ((is_shift | is_logic)? " r1, " : " r5,") << ((is_logic) ? "" :  " r1,") << " r1" << endl;
	test_cmp(5 , res, s);
}

void test_rr_dest_bypass(int num, int cycles, string inst, reg_t res, reg_t val1, reg_t val2,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	s << "MOVS r4, 0" << endl;
	s << "BYPASS" << num << ": ";
	li(1, val1, s);
	li(2, val2, s);
	s << inst << ((is_shift | is_logic)? " r1, " : " r5,") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	test_insert_nops(cycles);
	s << "ADDS r3, r5, 0" << endl;
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
	test_insert_nops(rs1_cycles);
	li(2, val2, s);
	test_insert_nops(rs2_cycles);
	s << inst << ((is_shift | is_logic)? " r1, " : " r5,") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	s << "ADDS r4, r4, 1" << endl;
	s << "MOVS r0, 2" << endl;
	s << "CMP r0, r4" << endl;
	s << "BNE BYPASS" << num << endl;
	s << "NOOP" << endl;
	test_cmp(5 , res, s);
}

void test_rr_rs21_bypass(int num, int rs1_cycles, int rs2_cycles, string inst, reg_t res, reg_t val1, reg_t val2,
	bool is_shift=false, bool is_logic=false, ostream& s=cout) {
	s << "MOVS r4, 0" << endl;
	s << "BYPASS" << num << ": ";
	li(2, val2, s);
	test_insert_nops(rs2_cycles);
	li(1, val1, s);
	test_insert_nops(rs1_cycles);
	s << inst << ((is_shift | is_logic)? " r1, " : " r5,") << ((is_logic) ? "" :  " r1,") << " r2" << endl;
	s << "ADDS r4, r4, 1" << endl;
	s << "MOVS r0, 2" << endl;
	s << "CMP r0, r4" << endl;
	s << "BNE BYPASS" << num << endl;
	s << "NOOP" << endl;
	test_cmp(5 , res, s);
}

#endif  // header _TEST_FUNC_H_