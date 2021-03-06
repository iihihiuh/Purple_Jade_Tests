#include "test_funcs.h"

uint16_t lsrs(uint16_t val1, uint16_t val2) {
	return val1 >> val2;
}

int main(int argc, char** argv) {
	// arithmetics 
	test_rr_op("LSRS", lsrs(0x8000,0), 0x8000, 0, true, false);
	test_rr_op("LSRS", lsrs(0x8000,1), 0x8000, 1, true, false);
	test_rr_op("LSRS", lsrs(0x8000,7), 0x8000, 7, true, false);
	test_rr_op("LSRS", lsrs(0x8000,14), 0x8000, 14, true, false);
	test_rr_op("LSRS", lsrs(0x8000,15), 0x8000, 15, true, false);

	test_rr_op("LSRS", lsrs(0xffff,0), 0xffff, 0, true, false);
	test_rr_op("LSRS", lsrs(0xffff,1), 0xffff, 1, true, false);
	test_rr_op("LSRS", lsrs(0xffff,7), 0xffff, 7, true, false);
	test_rr_op("LSRS", lsrs(0xffff,14), 0xffff, 14, true, false);
	test_rr_op("LSRS", lsrs(0xffff,15), 0xffff, 15, true, false);

	test_rr_op("LSRS", lsrs(0x2121,0), 0x2121, 0, true, false);
	test_rr_op("LSRS", lsrs(0x2121,1), 0x2121, 1, true, false);
	test_rr_op("LSRS", lsrs(0x2121,7), 0x2121, 7, true, false);
	test_rr_op("LSRS", lsrs(0x2121,14), 0x2121, 14, true, false);
	test_rr_op("LSRS", lsrs(0x2121,15), 0x2121, 15, true, false);

	// equal tests
	test_rr_rs1_eq_rs2("LSRS", 0, 7, true, false);

	// bypass tests
	test_rr_dest_bypass(1, 0, "LSRS", lsrs(0x8000,7), 0x8000, 7, true, false);
	test_rr_dest_bypass(2, 1, "LSRS", lsrs(0x8000,14), 0x8000, 14, true, false);
	test_rr_dest_bypass(3, 2, "LSRS", lsrs(0x8000,15), 0x8000, 15, true, false);

	test_rr_rs12_bypass(4, 0, 0, "LSRS", lsrs(0x8000,7), 0x8000, 7, true, false);
	test_rr_rs12_bypass(5, 0, 1, "LSRS", lsrs(0x8000,14), 0x8000, 14, true, false);
	test_rr_rs12_bypass(6, 0, 2, "LSRS", lsrs(0x8000,15), 0x8000, 15, true, false);
	test_rr_rs12_bypass(7, 1, 0, "LSRS", lsrs(0x8000,7), 0x8000, 7, true, false);
	test_rr_rs12_bypass(8, 1, 1, "LSRS", lsrs(0x8000,14), 0x8000, 14, true, false);
	test_rr_rs12_bypass(9, 2, 0, "LSRS", lsrs(0x8000,15), 0x8000, 15, true, false);

	test_rr_rs21_bypass(10, 0, 0, "LSRS", lsrs(0x8000,7), 0x8000, 7, true, false);
	test_rr_rs21_bypass(11, 0, 1, "LSRS", lsrs(0x8000,14), 0x8000, 14, true, false);
	test_rr_rs21_bypass(12, 0, 2, "LSRS", lsrs(0x8000,15), 0x8000, 15, true, false);
	test_rr_rs21_bypass(13, 1, 0, "LSRS", lsrs(0x8000,7), 0x8000, 7, true, false);
	test_rr_rs21_bypass(14, 1, 1, "LSRS", lsrs(0x8000,14), 0x8000, 14, true, false);
	test_rr_rs21_bypass(15, 2, 0, "LSRS", lsrs(0x8000,15), 0x8000, 15, true, false);
	return 0;
}