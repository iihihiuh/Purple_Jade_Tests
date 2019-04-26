#include "test_funcs.h"

int main(int argc, char** argv) {
	test_rimm_op("ADD", 0, 0, 0b000, true);
	test_rimm_op("ADD", 1, 0, 0b001, true);
	test_rimm_op("ADD", 3, 0, 0b010, true);
	test_rimm_op("ADD", 6, 0, 0b011, true);
	test_rimm_op("ADD", 10, 0, 0b100, true);
	test_rimm_op("ADD", 15, 0, 0b101, true);
	test_rimm_op("ADD", 21, 0, 0b110, true);
	test_rimm_op("ADD", 28, 0, 0b111, true);
	return 0;
}