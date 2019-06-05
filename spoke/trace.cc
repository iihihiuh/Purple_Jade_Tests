#include "processor.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Processor::printTrace() {
	cerr << setw(4) << setfill('0') << hex << log.pc;

	if (log.rd_write) {
		cerr << setw(1) << hex << 1;
		cerr << setw(4) << setfill('0') << hex << log.rd;
		cerr << setw(4) << setfill('0') << hex << log.rd_val;
	} else {
		cerr << setw(1) << hex << 0;
		cerr << setw(4) << setfill('0') << hex << 0;
		cerr << setw(4) << setfill('0') << hex << 0;
	}
	
	if (log.mem_access & !log.lors) {
		cerr << setw(1) << hex << !log.lors;
		cerr << setw(4) << setfill('0') << hex << log.addr;
		cerr << setw(4) << setfill('0') << hex << log.mem_val;
	} else {
		cerr << setw(1) << hex << 0;
		cerr << setw(4) << setfill('0') << hex << 0;
		cerr << setw(4) << setfill('0') << hex << 0;
	}
	uint32_t f = 0;
	if (C)
		f |= (0x1 << 3);
	if (N)
		f |= (0x1 << 2);
	if (Z)
		f |= (0x1 << 1);
	if (V)
		f |= 0x1;
	cerr << setw(1) << f << endl;
}