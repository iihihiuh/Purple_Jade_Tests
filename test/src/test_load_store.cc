#include "test_funcs.h"

int main(int argc, char** argv) {
	// basic with ld store bypass
	//               content c, base, offset
	test_ld_st_op(0xf0f0, 0, 0, 1);
	test_ld_st_op(0xfdf0, 0, 0, 3);
	test_ld_st_op(0xfaf4, 0, 0, 7);
	test_ld_st_op(0xf4fe, 0, 0, 13);
	test_ld_st_op(0xf4fe, 0, 0, 31);
	test_ld_st_op(0xf0f0, 0, 2, 1);
	test_ld_st_op(0xfdf0, 0, 4, 3);
	test_ld_st_op(0xfaf4, 0, 5, 7);
	test_ld_st_op(0xf4fe, 0, 6, 13);
	test_ld_st_op(0xf4fe, 0, 8, 31);

	test_ld_st_op(0xf3f0, 1, 0, 1);
	test_ld_st_op(0xfff0, 2, 0, 3);
	test_ld_st_op(0xfbf3, 3, 0, 7);
	test_ld_st_op(0xfdf6, 4, 0, 13);
	test_ld_st_op(0xf6ff, 5, 0, 31);
	test_ld_st_op(0xf6ff, 6, 0, 31);
	test_ld_st_op(0xf3f0, 1, 2, 1);
	test_ld_st_op(0xfff0, 2, 4, 3);
	test_ld_st_op(0xfbf3, 3, 5, 7);
	test_ld_st_op(0xfdf6, 4, 6, 13);
	test_ld_st_op(0xf6ff, 5, 7, 31);
	test_ld_st_op(0xf6ff, 6, 7, 31);

	// bypass tests
	// bypassing dest register
	test_ld_st_bypass(1, 0, 0, 0xfdf6, 0, 0, 1, false);
	test_ld_st_bypass(2, 0, 1, 0xf0f6, 0, 0, 3, false);
	test_ld_st_bypass(3, 0, 2, 0x0006, 0, 3, 4, false);
	test_ld_st_bypass(4, 0, 3, 0xf006, 0, 4, 14, false);
	test_ld_st_bypass(5, 0, 4, 0xf366, 0, 3, 31, false);
	test_ld_st_bypass(6, 0, 5, 0xfe66, 0, 5, 10, false);
	test_ld_st_bypass(7, 0, 6, 0xf046, 0, 6, 31, false);

	// bypassing rs1
	test_ld_st_bypass(8, 0, 0, 0x1411, 0, 0, 1, false);
	test_ld_st_bypass(9, 1, 0, 0xf5ff, 0, 0, 3, false);
	test_ld_st_bypass(10, 2, 0, 0x4464, 0, 3, 4, false);
	test_ld_st_bypass(11, 3, 0, 0x5643, 0, 4, 14, false);
	test_ld_st_bypass(12, 4, 0, 0x9d93, 0, 3, 31, false);
	test_ld_st_bypass(13, 5, 0, 0x9b93, 0, 5, 10, false);
	test_ld_st_bypass(14, 6, 0, 0x9a93, 0, 6, 31, false);


	// bypassing st register
	test_ld_st_bypass(15, 0, 0, 0x9e93, 0, 100, 1, true);
	test_ld_st_bypass(16, 1, 0, 0x98d3, 0, 100, 2, true);
	test_ld_st_bypass(17, 2, 0, 0xdead, 0, 100, 3, true);
	test_ld_st_bypass(18, 3, 0, 0xbeef, 0, 100, 4, true);
	test_ld_st_bypass(19, 4, 0, 0xabcd, 0, 100, 5, true);
	test_ld_st_bypass(20, 5, 0, 0xefab, 0, 100, 6, true);
	test_ld_st_bypass(21, 6, 0, 0xcdcd, 0, 100, 7, true);
	return 0;
}