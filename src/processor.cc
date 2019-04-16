#include "processor.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Processor::Processor() {
	regfile =  new reg_t[REGNUM];
	// addressable address space
	instr_mem = (reg_t*) new char[0x1 << (XLEN + 1)];
	data_mem =  new char[0x1 << (XLEN + 1)];
	LR = 0;
	SP = 0;
	PC = 0;
	inst_num = 0;
}

Processor::~Processor() {
	delete[] regfile;
	delete[] data_mem;
	delete[] instr_mem;
}

void Processor::load_program(string file, reg_t address) {
	assert(address % 2 == 0);

	ifstream programfile(file);
	string line;
	inst_num = 0;
	PC = address;
	// instructions are two bytes
	reg_t start = address >> 1;
	while (getline(programfile, line)) {
		if (line.find("//") == string::npos) {
			// not a comment
			reg_t inst = (reg_t) stoul(line, nullptr, 2);
			assert((uint64_t) start < (0x1 << (XLEN + 1)));
			instr_mem[start] = inst;
			start++;
			inst_num++;
		}
	}
}