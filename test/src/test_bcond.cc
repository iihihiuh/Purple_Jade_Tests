#include "test_funcs.h"

int main(int argc, char** argv) {
	// arithmetic
	li(1,0x7fff);
	li(2,0xffff);
	cout << "CMP r1, r2" << endl;
	// taken
	test_bcond_taken(1, 0, "EQ", 2, 2);
	test_bcond_taken(2, 0, "NE", 1, 2);
	test_bcond_taken(3, 0, "NE", 4, 2);
	test_bcond_taken(4, 0, "GE", 2, 2);
	test_bcond_taken(5, 0, "GE", 3, 2);
	test_bcond_taken(6, 0, "LT", 1, 2);
	test_bcond_taken(7, 0, "GT", 4, 2);
	test_bcond_taken(8, 0, "LE", 1, 2);
	test_bcond_taken(9, 0, "LE", 2, 2);
	test_bcond_taken(10, 0, "AL", 1, 2);
	test_bcond_taken(11, 0, "MI", 1, 2);
	test_bcond_taken(12, 0, "PL", 2, 2);
	test_bcond_taken(13, 0, "PL", 2, 1);
	test_bcond_taken(14, 0, "HI", 0x7fff, 0xffff);
	test_bcond_taken(15, 0, "LS", 1, 1);
	test_bcond_taken(16, 0, "LS", 4, 1);
	test_bcond_taken(17, 0, "CS", 0, 1);
	test_bcond_taken(18, 0, "CC", 1, 0);
	test_bcond_taken(19, 0, "VS", 0x7fff, 0xffff);
	test_bcond_taken(20, 0, "VC", 4, 1);

	// not taken
	test_bcond_not_taken(21, 0, "EQ", 1, 2);
	test_bcond_not_taken(22, 0, "NE", 2, 2);
	test_bcond_not_taken(23, 0, "GE", 1, 2);
	test_bcond_not_taken(24, 0, "LT", 3, 2);
	test_bcond_not_taken(25, 0, "LT", 2, 2);
	test_bcond_not_taken(26, 0, "GT", 2, 2);
	test_bcond_not_taken(27, 0, "GT", 1, 2);
	test_bcond_not_taken(28, 0, "LE", 4, 2);
	test_bcond_not_taken(29, 0, "MI", 2, 2);
	test_bcond_not_taken(30, 0, "MI", 4, 2);
	test_bcond_not_taken(31, 0, "PL", 2, 3);
	test_bcond_not_taken(32, 0, "HI", 0xffff, 0xffff);
	test_bcond_not_taken(33, 0, "LS", 0xffff, 0);
	test_bcond_not_taken(34, 0, "CC", 0, 1);
	test_bcond_not_taken(35, 0, "CS", 1, 0);
	test_bcond_not_taken(36, 0, "VC", 0x7fff, 0xffff);
	test_bcond_not_taken(37, 0, "VS", 4, 1);

	// bypass
	// taken
	test_bcond_taken(41, 1, "EQ", 2, 2);
	test_bcond_taken(42, 2, "NE", 1, 2);
	test_bcond_taken(43, 3, "NE", 4, 2);
	test_bcond_taken(44, 4, "GE", 2, 2);
	test_bcond_taken(45, 5, "GE", 3, 2);
	test_bcond_taken(46, 6, "LT", 1, 2);
	test_bcond_taken(47, 7, "GT", 4, 2);
	test_bcond_taken(48, 8, "LE", 1, 2);
	test_bcond_taken(49, 9, "LE", 2, 2);
	test_bcond_taken(410, 10, "AL", 1, 2);
	test_bcond_taken(411, 11, "MI", 1, 2);
	test_bcond_taken(412, 12, "PL", 2, 2);
	test_bcond_taken(413, 13, "PL", 2, 1);
	test_bcond_taken(414, 14, "HI", 0x7fff, 0xffff);
	test_bcond_taken(415, 15, "LS", 1, 1);
	test_bcond_taken(416, 16, "LS", 4, 1);
	test_bcond_taken(417, 17, "CS", 0, 1);
	test_bcond_taken(418, 18, "CC", 1, 0);
	test_bcond_taken(419, 19, "VS", 0x7fff, 0xffff);
	test_bcond_taken(420, 20, "VC", 4, 1);

 	// bypass
	// not taken
	test_bcond_not_taken(421, 0, "EQ", 1, 2);
	test_bcond_not_taken(422, 1, "NE", 2, 2);
	test_bcond_not_taken(423, 2, "GE", 1, 2);
	test_bcond_not_taken(424, 3, "LT", 3, 2);
	test_bcond_not_taken(425, 4, "LT", 2, 2);
	test_bcond_not_taken(426, 5, "GT", 2, 2);
	test_bcond_not_taken(427, 6, "GT", 1, 2);
	test_bcond_not_taken(428, 7, "LE", 4, 2);
	test_bcond_not_taken(429, 8, "MI", 2, 2);
	test_bcond_not_taken(430, 9, "MI", 4, 2);
	test_bcond_not_taken(431, 10, "PL", 2, 3);
	test_bcond_not_taken(432, 11, "HI", 0xffff, 0xffff);
	test_bcond_not_taken(433, 12, "LS", 0xffff, 0);
	test_bcond_not_taken(434, 13, "CC", 0, 1);
	test_bcond_not_taken(435, 14, "CS", 1, 0);
	test_bcond_not_taken(436, 15, "VC", 0x7fff, 0xffff);
	test_bcond_not_taken(437, 16, "VS", 4, 1);


	return 0;
}