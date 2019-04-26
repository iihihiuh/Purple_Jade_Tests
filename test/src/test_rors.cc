#include "test_funcs.h"

uint16_t rors(uint16_t val1, uint16_t val2) {
	val2 = val2 % XLEN; 
 	uint16_t hi = val1 << (XLEN - val2);
 	uint16_t lo = val1 >> val2;
 	uint16_t res = lo | hi;
 	return res;
 }

int main(int argc, char** argv) {
	// arithmetics 
	test_rr_op("RORS", rors(0x8000,0), 0x8000, 0, true, false);
	test_rr_op("RORS", rors(0x8000,1), 0x8000, 1, true, false);
	test_rr_op("RORS", rors(0x8000,7), 0x8000, 7, true, false);
	test_rr_op("RORS", rors(0x8000,14), 0x8000, 14, true, false);
	test_rr_op("RORS", rors(0x8000,15), 0x8000, 15, true, false);

	test_rr_op("RORS", rors(0x7fff,0), 0x7fff, 0, true, false);
	test_rr_op("RORS", rors(0x7fff,1), 0x7fff, 1, true, false);
	test_rr_op("RORS", rors(0x7fff,7), 0x7fff, 7, true, false);
	test_rr_op("RORS", rors(0x7fff,14), 0x7fff, 14, true, false);
	test_rr_op("RORS", rors(0x7fff,15), 0x7fff, 15, true, false);

	test_rr_op("RORS", rors(0x8181,0), 0x8181, 0, true, false);
	test_rr_op("RORS", rors(0x8181,1), 0x8181, 1, true, false);
	test_rr_op("RORS", rors(0x8181,7), 0x8181, 7, true, false);
	test_rr_op("RORS", rors(0x8181,14), 0x8181, 14, true, false);
	test_rr_op("RORS", rors(0x8181,15), 0x8181, 15, true, false);

	// equal tests
	test_rr_rs1_eq_rs2("RORS", rors(7,7), 7, true, false);

	// bypass tests
	test_rr_dest_bypass(1, 0, "RORS", rors(0x8000,7), 0x8000, 7, true, false);
	test_rr_dest_bypass(2, 1, "RORS", rors(0x8000,14), 0x8000, 14, true, false);
	test_rr_dest_bypass(3, 2, "RORS", rors(0x8000,15), 0x8000, 15, true, false);

	test_rr_rs12_bypass(4, 0, 0, "RORS", rors(0x8000,7), 0x8000, 7, true, false);
	test_rr_rs12_bypass(5, 0, 1, "RORS", rors(0x8000,14), 0x8000, 14, true, false);
	test_rr_rs12_bypass(6, 0, 2, "RORS", rors(0x8000,15), 0x8000, 15, true, false);
	test_rr_rs12_bypass(7, 1, 0, "RORS", rors(0x8000,7), 0x8000, 7, true, false);
	test_rr_rs12_bypass(8, 1, 1, "RORS", rors(0x8000,14), 0x8000, 14, true, false);
	test_rr_rs12_bypass(9, 2, 0, "RORS", rors(0x8000,15), 0x8000, 15, true, false);

	test_rr_rs21_bypass(10, 0, 0, "RORS", rors(0x8000,7), 0x8000, 7, true, false);
	test_rr_rs21_bypass(11, 0, 1, "RORS", rors(0x8000,14), 0x8000, 14, true, false);
	test_rr_rs21_bypass(12, 0, 2, "RORS", rors(0x8000,15), 0x8000, 15, true, false);
	test_rr_rs21_bypass(13, 1, 0, "RORS", rors(0x8000,7), 0x8000, 7, true, false);
	test_rr_rs21_bypass(14, 1, 1, "RORS", rors(0x8000,14), 0x8000, 14, true, false);
	test_rr_rs21_bypass(15, 2, 0, "RORS", rors(0x8000,15), 0x8000, 15, true, false);

	// make sure only use lower 4 bits
	test_rr_op("RORS", rors(0xff81,0xffc0), 0xff81, 0xffc0, true, false);
	test_rr_op("RORS", rors(0xff81,0xffc1), 0xff81, 0xffc1, true, false);
	test_rr_op("RORS", rors(0xff81,0xffc7), 0xff81, 0xffc7, true, false);
	test_rr_op("RORS", rors(0xff81,0xffce), 0xff81, 0xffce, true, false);
	test_rr_op("RORS", rors(0xff81,0xffff), 0xff81, 0xffff, true, false);
	return 0;
}