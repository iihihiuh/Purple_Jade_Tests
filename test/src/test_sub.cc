#include "test_funcs.h"

uint16_t subs(uint16_t val1, uint16_t val2) {
	return val1 + ~(val2) + 1;
}

int main(int argc, char** argv) {
	// arithmetics 
	test_rr_op("SUBS", subs(0,0), 0, 0);
	test_rr_op("SUBS", subs(1,1), 1, 1);
	test_rr_op("SUBS", subs(3,7), 3, 7);

	test_rr_op("SUBS", subs(0x0000,0xf800), 0x0000, 0xf800);
	test_rr_op("SUBS", subs(0xf800,0x0000), 0xf800, 0x0000);
	test_rr_op("SUBS", subs(0xf800,0xff80), 0xf800, 0xff80);

	test_rr_op("SUBS", subs(0x0000,0x7fff), 0x0000, 0x7fff);
	test_rr_op("SUBS", subs(0x7fff,0x0000), 0x7fff, 0x0000);
	test_rr_op("SUBS", subs(0x7fff,0x007f), 0x7fff, 0x007f);
	
	test_rr_op("SUBS", subs(0xf800,0x007f), 0xf800, 0x007f);
	test_rr_op("SUBS", subs(0x7fff,0xff80), 0x7fff, 0xff80);

	test_rr_op("SUBS", subs(0x0000,0xffff), 0x0000, 0xffff);
	test_rr_op("SUBS", subs(0xffff,0x0001), 0xffff, 0x0001);
	test_rr_op("SUBS", subs(0xffff,0xffff), 0xffff, 0xffff);

	// equal tests
	test_rr_rs1_eq_dest("SUBS", 24, 13, 11);
	test_rr_rs2_eq_dest("SUBS", 25, 13, 12);
	test_rr_rs1_eq_rs2("SUBS", 26, 13);

	// bypass tests
	test_rr_dest_bypass(1, 0, "SUBS", 2, 13, 11);
	test_rr_dest_bypass(2, 1, "SUBS", 3, 14, 11);
	test_rr_dest_bypass(3, 2, "SUBS", 0, 13, 13);

	test_rr_rs12_bypass(4, 0, 0, "SUBS", 2, 13, 11);
	test_rr_rs12_bypass(5, 0, 1, "SUBS", 3, 14, 11);
	test_rr_rs12_bypass(6, 0, 2, "SUBS", 4, 15, 11);
	test_rr_rs12_bypass(7, 1, 0, "SUBS", 2, 13, 11);
	test_rr_rs12_bypass(8, 1, 1, "SUBS", 5, 16, 11);
	test_rr_rs12_bypass(9, 2, 0, "SUBS", 6, 5, 0xffff);

	test_rr_rs21_bypass(10, 0, 0, "SUBS", 2, 13, 11);
	test_rr_rs21_bypass(11, 0, 1, "SUBS", 3, 14, 11);
	test_rr_rs21_bypass(12, 0, 2, "SUBS", 4, 15, 11);
	test_rr_rs21_bypass(13, 1, 0, "SUBS", 2, 13, 11);
	test_rr_rs21_bypass(14, 1, 1, "SUBS", 5, 16, 11);
	test_rr_rs21_bypass(15, 2, 0, "SUBS", 6, 5, 0xffff);
	return 0;
}