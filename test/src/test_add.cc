#include "test_funcs.h"

int main(int argc, char** argv) {
	// arithmetics 
	test_rr_op("ADDS", 0, 0, 0);
	test_rr_op("ADDS", 2, 1, 1);
	test_rr_op("ADDS", 10, 3, 7);

	test_rr_op("ADDS", 0xf800, 0x0000, 0xf800);
	test_rr_op("ADDS", 0xf800, 0xf800, 0x0000);
	test_rr_op("ADDS", 0xf780, 0xf800, 0xff80);

	test_rr_op("ADDS", 0x7fff, 0x0000, 0x7fff);
	test_rr_op("ADDS", 0x7fff, 0x7fff, 0x0000);
	test_rr_op("ADDS", 0x807e, 0x7fff, 0x007f);
	
	test_rr_op("ADDS", 0xf87f, 0xf800, 0x007f);
	test_rr_op("ADDS", 0x7f7f, 0x7fff, 0xff80);

	test_rr_op("ADDS", 0xffff, 0x0000, 0xffff);
	test_rr_op("ADDS", 0x0000, 0xffff, 0x0001);
	test_rr_op("ADDS", 0xfffe, 0xffff, 0xffff);

	// equal tests
	test_rr_rs1_eq_dest("ADDS", 24, 13, 11);
	test_rr_rs2_eq_dest("ADDS", 25, 13, 12);
	test_rr_rs1_eq_rs2("ADDS", 26, 13);

	// bypass tests
	test_rr_dest_bypass(1, 0, "ADDS", 24, 13, 11);
	test_rr_dest_bypass(2, 1, "ADDS", 25, 13, 12);
	test_rr_dest_bypass(3, 2, "ADDS", 26, 13, 13);

	test_rr_rs12_bypass(4, 0, 0, "ADDS", 24, 13, 11);
	test_rr_rs12_bypass(5, 0, 1, "ADDS", 25, 14, 11);
	test_rr_rs12_bypass(6, 0, 2, "ADDS", 26, 15, 11);
	test_rr_rs12_bypass(7, 1, 0, "ADDS", 24, 13, 11);
	test_rr_rs12_bypass(8, 1, 1, "ADDS", 26, 15, 11);
	test_rr_rs12_bypass(9, 2, 0, "ADDS", 27, 13, 14);

	test_rr_rs21_bypass(10, 0, 0, "ADDS", 24, 13, 11);
	test_rr_rs21_bypass(11, 0, 1, "ADDS", 25, 14, 11);
	test_rr_rs21_bypass(12, 0, 2, "ADDS", 26, 15, 11);
	test_rr_rs21_bypass(13, 1, 0, "ADDS", 24, 13, 11);
	test_rr_rs21_bypass(14, 1, 1, "ADDS", 26, 15, 11);
	test_rr_rs21_bypass(15, 2, 0, "ADDS", 27, 13, 14);
	return 0;
}