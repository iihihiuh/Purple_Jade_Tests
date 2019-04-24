#include "test_funcs.h"

int main(int argc, char** argv) {
	test_rr_op("ANDS",  8,  1, 3, false, true);
	test_rr_rs1_eq_dest("ANDS",  8,  1, 3, false, true);
	test_rr_rs2_eq_dest("ANDS",  8,  1, 3, false, true);
	test_rr_rs1_eq_rs2("ANDS",  2,  1, false, true);
	test_rr_dest_bypass(1, 3, "ANDS",  8,  1, 3, false, true);
	test_rr_rs12_bypass(2, 3, 3, "ANDS",  8,  1, 3, false, true);
	test_rr_rs21_bypass(3, 3, 4, "ANDS",  8,  1, 3, false, true);
	return 0;
}