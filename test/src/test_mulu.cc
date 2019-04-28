#include "test_funcs.h"

uint16_t mulu(uint16_t val1, uint16_t val2) {
	return val1 * val2;
}

int main(int argc, char** argv) {
	// arithmetics 
	test_rr_op("MULU", mulu(0,0), 0, 0, true, false);
	test_rr_op("MULU", mulu(1,1), 1, 1, true, false);
	test_rr_op("MULU", mulu(3,7), 3, 7, true, false);

	test_rr_op("MULU", mulu(0x0000,0xf800), 0x0000, 0xf800, true, false);
	test_rr_op("MULU", mulu(0xf800,0x0000), 0xf800, 0x0000, true, false);
	test_rr_op("MULU", mulu(0xf800,0xff80), 0xf800, 0xff80, true, false);

	test_rr_op("MULU", mulu(0x0000,0x7fff), 0x0000, 0x7fff, true, false);
	test_rr_op("MULU", mulu(0x7fff,0x0000), 0x7fff, 0x0000, true, false);
	test_rr_op("MULU", mulu(0x7fff,0x007f), 0x7fff, 0x007f, true, false);

	test_rr_op("MULU", mulu(0xf800,0x007f), 0xf800, 0x007f, true, false);
	test_rr_op("MULU", mulu(0x7fff,0xff80), 0x7fff, 0xff80, true, false);

	test_rr_op("MULU", mulu(0x0000,0xffff), 0x0000, 0xffff, true, false);
	test_rr_op("MULU", mulu(0xffff,0x0001), 0xffff, 0x0001, true, false);
	test_rr_op("MULU", mulu(0xffff,0xffff), 0xffff, 0xffff, true, false);

	// equal tests
	test_rr_rs1_eq_dest("MULU", mulu(13,11), 13, 11, true, false);
	test_rr_rs2_eq_dest("MULU", mulu(14,11), 13, 12, true, false);
	test_rr_rs1_eq_rs2("MULU", mulu(13,13), 13, true, false);

	// bypass tests
	test_rr_dest_bypass(1, 0, "MULU", mulu(13,11), 13, 11, true, false);
	test_rr_dest_bypass(2, 1, "MULU", mulu(14,11), 13, 12, true, false);
	test_rr_dest_bypass(3, 2, "MULU", mulu(13,13), 13, 13, true, false);

	test_rr_rs12_bypass(4, 0, 0, "MULU", mulu(13,11), 13, 11, true, false);
	test_rr_rs12_bypass(5, 0, 1, "MULU", mulu(14,11), 14, 11, true, false);
	test_rr_rs12_bypass(6, 0, 2, "MULU", mulu(15,11), 15, 11, true, false);
	test_rr_rs12_bypass(7, 1, 0, "MULU", mulu(13,11), 13, 11, true, false);
	test_rr_rs12_bypass(8, 1, 1, "MULU", mulu(14,11), 15, 11, true, false);
	test_rr_rs12_bypass(9, 2, 0, "MULU", mulu(13,14), 13, 14, true, false);

	test_rr_rs21_bypass(10, 0, 0, "MULU", mulu(13,11), 13, 11, true, false);
	test_rr_rs21_bypass(11, 0, 1, "MULU", mulu(14,11), 14, 11, true, false);
	test_rr_rs21_bypass(12, 0, 2, "MULU", mulu(15,11), 15, 11, true, false);
	test_rr_rs21_bypass(13, 1, 0, "MULU", mulu(13,11), 13, 11, true, false);
	test_rr_rs21_bypass(14, 1, 1, "MULU", mulu(14,11), 15, 11, true, false);
	test_rr_rs21_bypass(15, 2, 0, "MULU", mulu(13,14), 13, 14, true, false);
	return 0;
}