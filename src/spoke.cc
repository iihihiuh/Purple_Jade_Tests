#include "encoding.h"
#include "processor.h"

int main() {

	Processor core = Processor();
	core.load_program("../asm/test0.bin", (reg_t)0);
	core.start();
	return 0;
}