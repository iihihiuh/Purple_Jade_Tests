#include "test_funcs.h"

uint16_t subs(uint16_t val1, uint16_t val2) {
	return val1 + ~(val2) + 1;
}

int main(int argc, char** argv) {
	// arithmetics 
	test_rimm_op("SUBS", 0, 0, 0b0);
	test_rimm_op("SUBS", 0, 1, 0b1);
	test_rimm_op("SUBS", subs(3, 0b111), 3, 0b111);

	test_rimm_op("SUBS", subs(0, 0b100), 0x0000, 0b100);
	test_rimm_op("SUBS", subs(4, 0), 0x0004, 0b000);
	
	test_rimm_op("SUBS", subs(0, 0b111), 0, 0b111);
	test_rimm_op("SUBS", subs(0xffff, 0b001), 0xffff, 0b001);
	test_rimm_op("SUBS", subs(0x0001, 0b111), 0x0001, 0b111);

	// eq test
	test_rimm_eq_dst("SUBS", 12, 18, 6);

	// bypassing tests
	// src bypassing
	test_rimm_bypass(1, 0, 0, "SUBS", 6, 13, 7);
	test_rimm_bypass(2, 1, 0, "SUBS", 10, 13, 3);
	test_rimm_bypass(3, 2, 0, "SUBS", 12, 13, 1);
	test_rimm_bypass(4, 3, 0, "SUBS", 13, 20, 7);
	test_rimm_bypass(5, 4, 0, "SUBS", 17, 20, 3);
	test_rimm_bypass(6, 5, 0, "SUBS", 19, 20, 1);

	// dest bypassing
	test_rimm_bypass(7, 0, 0, "SUBS", 6, 13, 7);
	test_rimm_bypass(8, 0, 1, "SUBS", 10, 13, 3);
	test_rimm_bypass(9, 0, 2, "SUBS", 12, 13, 1);
	test_rimm_bypass(10, 0, 3, "SUBS", 13, 20, 7);
	test_rimm_bypass(11, 0, 4, "SUBS", 17, 20, 3);
	test_rimm_bypass(12, 0, 5, "SUBS", 19, 20, 1);
	return 0;
}