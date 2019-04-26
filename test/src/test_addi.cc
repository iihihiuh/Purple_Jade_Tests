#include "test_funcs.h"

int main(int argc, char** argv) {
	// arithmetics 
	test_rimm_op("ADDS", 0, 0, 0b0);
	test_rimm_op("ADDS", 2, 1, 0b1);
	test_rimm_op("ADDS", 10, 3, 0b111);

	test_rimm_op("ADDS", 0x0004, 0x0000, 0b100);
	test_rimm_op("ADDS", 0x0004, 0x0004, 0b000);
	
	test_rimm_op("ADDS", 7, 0, 0b111);
	test_rimm_op("ADDS", 10, 0xffff, 0b001);
	test_rimm_op("ADDS", 8, 0x0001, 0b111);

	// eq test
	test_rimm_eq_dst("ADDS", 24, 18, 6);

	// bypassing tests
	// src bypassing
	test_rimm_bypass(1, 0, 0, "ADDS", 20, 13, 7);
	test_rimm_bypass(2, 1, 0, "ADDS", 16, 13, 3);
	test_rimm_bypass(3, 2, 0, "ADDS", 14, 13, 1);
	test_rimm_bypass(4, 3, 0, "ADDS", 27, 20, 7);
	test_rimm_bypass(5, 4, 0, "ADDS", 23, 20, 3);
	test_rimm_bypass(6, 5, 0, "ADDS", 21, 20, 1);

	// dest bypassing
	test_rimm_bypass(7, 0, 0, "ADDS", 20, 13, 7);
	test_rimm_bypass(8, 0, 1, "ADDS", 16, 13, 3);
	test_rimm_bypass(9, 0, 2, "ADDS", 14, 13, 1);
	test_rimm_bypass(10, 0, 3, "ADDS", 27, 20, 7);
	test_rimm_bypass(11, 0, 4, "ADDS", 23, 20, 3);
	test_rimm_bypass(12, 0, 5, "ADDS", 21, 20, 1);
	return 0;
}