#include "processor.h"
#include "encoding.h"
#include "util.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Processor::Processor() {
	regfile =  new reg_t[REGNUM];
	// addressable address space
	instr_mem = (reg_t*) new char[0x1 << (XLEN + 1)];
	data_mem =  (reg_t*)new char[0x1 << (XLEN + 1)];
	LR = SP = PC = 0;
	N = Z = V = C = false;
	inst_num = 0;

	log.rs2_read = log.rs1_read = false;
	log.rd_write = false;
	log.N = log.Z = log.V = log.C = false;
	log.mem_access = false;
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
		}
	}
}

reg_t Processor::getReg(reg_t regnum) {
	assert(regnum < REGMAX);
	
	reg_t val = 0;

	if (regnum < REGNUM) {
		val = regfile[regnum];
	} else if (regnum == 13) {  // stack pointer
		val = SP;
	} else if (regnum == 14) { // link register
		val = LR;
	} else {
	  val = PC;  // PC
	}

	// loging
	if (log.rs1_read) {
		log.rs2_read = true;
		log.rs2 = regnum;
		log.rs2_val = val;
	} else {
		log.rs1_read = true;
		log.rs1 = regnum;
		log.rs1_val = val;
	}
	return val;
}
 
void Processor::setReg(reg_t regnum, reg_t val) {
	assert(regnum < REGMAX);

	if (regnum < REGNUM) {
		regfile[regnum] = val;
	} 

	if (regnum == 13) {  // stack pointer
		SP = val;
	} else if (regnum == 14) { // link register
		LR = val;
	}
	PC = val;  // PC

	// loging
	log.rd_write = true;
 	log.rd = regnum;
 	log.rd_val = val;
}

reg_t Processor::getMem(reg_t addr) {
	assert(addr % 2 == 0);
	reg_t idx = addr >> 1;
	reg_t val = data_mem[idx];

	// loging
	log.mem_access = true;
	log.lors = true;
	log.mem_val = val;
	log.addr = addr;

	return val;
}

void Processor::setMem(reg_t addr, reg_t val) {
	assert(addr % 2 == 0);
	reg_t idx = addr >> 1;

	data_mem[idx] = val;

	// loging
	log.mem_access = true;
	log.lors = false;
	log.mem_val = val;
	log.addr = addr;
}

 void Processor::step() {
 	assert(PC % 2 == 0);
 	Instr ins = instr_mem[PC >> 1];
 	if (match_MOVS(ins)) {
 		reg_t rd = get_bits(ins, 8, 3);
 		reg_t imm8 = get_bits(ins,0, 8);
 		setReg(rd, imm8);
 
 		// logging
 		log_imm(imm8);
 	} else if (match_MOV(ins)) {

 	}
 }