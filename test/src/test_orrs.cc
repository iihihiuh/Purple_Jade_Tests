#include "test_funcs.h"

uint16_t orrs(uint16_t val1, uint16_t val2) {
	return val1 | val2;
}

int main(int argc, char** argv) {
	// arithmetics 
	test_rr_op("ORRS", orrs(0xff00,0x0f0f), 0xff00, 0x0f0f, false, true);
	test_rr_op("ORRS", orrs(0x0ff0,0xf0f0), 0x0ff0, 0xf0f0, false, true);
	test_rr_op("ORRS", orrs(0xf00f,0xf0f0), 0xf00f, 0xf0f0, false, true);

	// equal tests
	test_rr_rs1_eq_dest("ORRS", orrs(0xff00,0x0f0f), 0xff00, 0x0f0f, false, true);
	test_rr_rs2_eq_dest("ORRS", orrs(0x0ff0,0xf0f0), 0x0ff0, 0xf0f0, false, true);
	test_rr_rs1_eq_rs2("ORRS", 0xff00, 0xff00, false, true);

	// bypass tests
	test_rr_dest_bypass(1, 0, "ORRS", orrs(0xff00,0x0f0f), 0xff00, 0x0f0f, false, true);
	test_rr_dest_bypass(2, 1, "ORRS", orrs(0x0ff0,0xf0f0), 0x0ff0, 0xf0f0, false, true);
	test_rr_dest_bypass(3, 2, "ORRS", orrs(0x00ff,0x0f0f), 0x00ff, 0x0f0f, false, true);

	test_rr_rs12_bypass(4, 0, 0, "ORRS", orrs(0xff00,0x0f0f), 0xff00, 0x0f0f, false, true);
	test_rr_rs12_bypass(5, 0, 1, "ORRS", orrs(0x0ff0,0xf0f0), 0x0ff0, 0xf0f0, false, true);
	test_rr_rs12_bypass(6, 0, 2, "ORRS", orrs(0xf00f,0xf0f0), 0xf00f, 0xf0f0, false, true);
	test_rr_rs12_bypass(7, 1, 0, "ORRS", orrs(0xff00,0x0f0f), 0xff00, 0x0f0f, false, true);
	test_rr_rs12_bypass(8, 1, 1, "ORRS", orrs(0x0ff0,0xf0f0), 0x0ff0, 0xf0f0, false, true);
	test_rr_rs12_bypass(9, 2, 0, "ORRS", orrs(0xf00f,0xf0f0), 0xf00f, 0xf0f0, false, true);

	test_rr_rs21_bypass(10, 0, 0, "ORRS", orrs(0xff00,0x0f0f), 0xff00, 0x0f0f, false, true);
	test_rr_rs21_bypass(11, 0, 1, "ORRS", orrs(0x0ff0,0xf0f0), 0x0ff0, 0xf0f0, false, true);
	test_rr_rs21_bypass(12, 0, 2, "ORRS", orrs(0xf00f,0xf0f0), 0xf00f, 0xf0f0, false, true);
	test_rr_rs21_bypass(13, 1, 0, "ORRS", orrs(0xff00,0x0f0f), 0xff00, 0x0f0f, false, true);
	test_rr_rs21_bypass(14, 1, 1, "ORRS", orrs(0x0ff0,0xf0f0), 0x0ff0, 0xf0f0, false, true);
	test_rr_rs21_bypass(15, 2, 0, "ORRS", orrs(0xf00f,0xf0f0), 0xf00f, 0xf0f0, false, true);
	return 0;
}