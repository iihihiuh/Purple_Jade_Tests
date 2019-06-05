#include "processor.h"
#include "encoding.h"
#include "util.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

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
	log.mem_access = false;
}

Processor::~Processor() {
	delete[] regfile;
	delete[] data_mem;
	delete[] instr_mem;
}

void Processor::load_program(string file, reg_t address) {
	ifstream programfile(file);
	string line;
	inst_num = 0;
	PC = address;
	// instructions are two bytes
	reg_t start = address;
	while (getline(programfile, line)) {
		if (line.find("//") == string::npos) {
			// not a comment
			reg_t inst = (reg_t) stoul(line, nullptr, 2);
			assert((uint64_t) start < (0x1 << (XLEN + 1)));
			instr_mem[start] = inst;
			start++;
		}
	}
	instr_mem[start] = 0x0000;
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
	} else if (regnum == 15) {

		PC = val;  // PC
	}
	// loging
	log.rd_write = true;
 	log.rd = regnum;
 	log.rd_val = val;
}

reg_t Processor::getMem(reg_t addr) {
	reg_t idx = addr;
	reg_t val = data_mem[idx];

	// loging
	log.mem_access = true;
	log.lors = true;
	log.mem_val = val;
	log.addr = addr;

	return val;
}

void Processor::setMem(reg_t addr, reg_t val) {
	reg_t idx = addr;

	data_mem[idx] = val;

	// loging
	log.mem_access = true;
	log.lors = false;
	log.mem_val = val;
	log.addr = addr;
}

 void Processor::setFlagNZ(reg_t val) {
 	int16_t s16 = static_cast<int16_t>(val);

 	N = s16 < 0;

	Z = val == (reg_t) 0;
 }

void Processor::start(bool trace) {
	while(1) {
		step(trace);
	}
}

void Processor::printLog() {
	cout << "PC " << log.pc << endl;
	if (log.rs1_read) {
		log.rs1_read = false;
		cout << "rs1 " << log.rs1 << " "<< log.rs1_val << endl;
	}

	if (log.rs2_read) {
		log.rs2_read = false;
		cout << "rs2 " << log.rs2 << " "<< log.rs2_val << endl;
	}

	if (log.imm_read) {
		log.imm_read = false;
		cout << "imm " << hex << log.imm_val << endl; 
	}

	if (log.rd_write) {
		log.rd_write = false;
		cout << "rd " << log.rd << " "<< log.rd_val << endl;
	}


	if (log.mem_access) {
		log.mem_access = false;
		if (log.lors) {
			cout << "load ";
		} else {
			cout << "store ";
		}
		cout << "address " << log.addr << " val " << log.mem_val << endl;
	}

	cout << "CNZV ";
	cout << ((C) ? "1" : "0");
	cout << ((N) ? "1" : "0");
	cout << ((Z) ? "1" : "0");
	cout << ((V) ? "1" : "0") << endl;
}

 void Processor::step(bool trace) {
 	Instr ins = instr_mem[PC];
 	log.pc = PC;
 	bool good = true;
 	cout << "Instr ";
 	if (match_MOVS(ins)) {
 		cout << "MOVS" << endl;
 		reg_t rd = get_bits(ins, 8, 3);
 		reg_t imm8 = get_bits(ins,0, 8);
 		setReg(rd, imm8);
 		setFlagNZ(imm8);
 		// logging
 		log_imm(imm8);
 	} else if (match_MOV(ins)) {
 		 cout << "MOV" << endl;

 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rm = get_bits(ins, 3, 4);
 		reg_t res = getReg(rm);
 		setReg(rd, res);
 	} else if (match_ADDIMM(ins)) {
  		cout << "ADD IMM" << endl;

 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t imm3 = get_bits(ins, 6, 3);
 		reg_t rm_val = getReg(rm);

 		reg_t res = add(imm3, rm_val);

 		setReg(rd, res);
 		setFlagNZ(res);

 		// loging
 		log_imm((reg_t) imm3);
 	} else if (match_ADDREG(ins)) {
 		cout << "ADD REG" << endl;
		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rn = get_bits(ins, 3, 3);
 		reg_t rm = get_bits(ins, 6, 3);
 		reg_t rm_val = getReg(rm);
 		reg_t rn_val = getReg(rn);

 		reg_t res = add(rm_val, rn_val);
 		setReg(rd, res);
 		setFlagNZ(res);

 	} else if (match_ADDSP(ins)) {
 		cout << "ADD SP" << endl;
 		reg_t imm7 = get_bits(ins, 0, 7);
 		reg_t sp_val = getReg(13);
 		reg_t res = add(sp_val, imm7, false);
 		setReg(13, res);

 		// loging 
 		log_imm(imm7);
 	} else if (match_SUBREG(ins)) {
 		cout << "SUB REG" << endl;
		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rn = get_bits(ins, 3, 3);
 		reg_t rm = get_bits(ins, 6, 3);
 		reg_t rm_val = getReg(rm);
 		reg_t rn_val = getReg(rn);

 		reg_t res = sub(rn_val, rm_val);
 		setReg(rd, res);
 		setFlagNZ(res);
 	} else if (match_SUBIMM(ins)) {
 		cout << "SUB IMM" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t imm3 = get_bits(ins, 6, 3);
 		reg_t rm_val = getReg(rm);

 		reg_t res = sub(rm_val, imm3);

 		setReg(rd, res);
 		setFlagNZ(res);

 		// loging
 		log_imm((reg_t) imm3);	
 	} else if (match_SUBSP(ins)) {
 		cout << "SUB SP" << endl;
		reg_t imm7 = get_bits(ins, 0, 7);
 		reg_t sp_val = getReg(13);
 		reg_t res = sub(sp_val, imm7, false);
 		setReg(13, res);

 		// loging 
 		log_imm(imm7);
 	} else if (match_CMP(ins)) {
 		cout << "CMP" << endl;
 		reg_t rn = get_bits(ins, 0, 3);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rn_val = getReg(rn);
 		reg_t rm_val = getReg(rm);
 		reg_t res = sub(rn_val, rm_val);

 		setFlagNZ(res);
 	} else if (match_AND(ins)) {
 		cout << "AND" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rd_val = getReg(rd);
 		reg_t rm_val = getReg(rm);
 		reg_t res = rd_val & rm_val;
 		setReg(rd, res);
 		setFlagNZ(res);
 	} else if (match_EOR(ins)) {
 		cout << "EOR" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rd_val = getReg(rd);
 		reg_t rm_val = getReg(rm);
 		reg_t res = rd_val ^ rm_val;
 		setReg(rd, res);
 		setFlagNZ(res);
 	} else if (match_OR(ins)) {
 		cout << "OR" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rd_val = getReg(rd);
 		reg_t rm_val = getReg(rm);
 		reg_t res = rd_val | rm_val;
 		setReg(rd, res);
 		setFlagNZ(res);
 	} else if (match_MVNS(ins)) {
 		cout << "MVNS" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rm_val = getReg(rm);
 		reg_t res =  ~rm_val;
 		setReg(rd, res);
 		setFlagNZ(res);
 	} else if (match_LSLS(ins)) {
 		cout << "LSLS" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rd_val = getReg(rd);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rm_val = getReg(rm);
 		reg_t res = rd_val << rm_val;

		//
 		C = get_bits(rd_val, (XLEN - rm_val), 1);

 		if (rd_val == 0 | rm_val > 16)
 			C = false;
 		//

		setReg(rd, res);
 		setFlagNZ(res);
 	} else if (match_LSRS(ins)) {
 		cout << "LSRS" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rd_val = getReg(rd);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rm_val = getReg(rm);
 		reg_t res = rd_val >> rm_val;

 		//

 		C = (rd_val >> (rm_val - 1)) & 0x1;

 		//

		setReg(rd, res);
 		setFlagNZ(res);
 	} else if (match_ASRS(ins)) {
 		cout << "ASRS" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
  		reg_t rd_val = getReg(rd);
		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rm_val = getReg(rm);		

 		int16_t rd_sval = static_cast<int16_t>(rd_val);
 		int16_t old_s = rd_sval;
 		rd_sval = rd_sval >> rm_val;
 		reg_t res = static_cast<reg_t>(rd_sval);
		//

 		C = (old_s >> (rm_val - 1)) & 0x1;

 		//
		setReg(rd, res);
 		setFlagNZ(res);
 	} else if (match_RORS(ins)) {
 		cout << "RORS" << endl;
  		reg_t rd = get_bits(ins, 0, 3);
  		reg_t rd_val = getReg(rd);
		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rm_val = getReg(rm);
 		rm_val = rm_val % XLEN; 

 		reg_t hi = get_bits(rd_val, 0, rm_val);
 		hi = hi << (XLEN - rm_val);
 		reg_t lo = rd_val >> rm_val;
 		reg_t res = lo | hi;

 		//

 		C = res >> (XLEN - 1);

 		//

		setReg(rd, res);
 		setFlagNZ(res);
 	} else if (match_ST(ins)) {
 		cout << "ST" << endl;
   		reg_t rd = get_bits(ins, 0, 3);
  		reg_t rd_val = getReg(rd);
		reg_t rn = get_bits(ins, 3, 3);
 		reg_t rn_val = getReg(rn);
 		reg_t imm5 = get_bits(ins, 6, 5);

 		reg_t addr = imm5 + rn_val;

 		setMem(addr, rd_val);
 		log_imm(imm5);
 	} else if (match_MULU(ins)) {
 		cout << "MULU" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rd_val = getReg(rd);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rm_val = getReg(rm);
 		reg_t res = rd_val * rm_val;
		setReg(rd, res);
 	} else if (match_DIVU(ins)) {
 		cout << "DIVU" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
 		reg_t rd_val = getReg(rd);
 		reg_t rm = get_bits(ins, 3, 3);
 		reg_t rm_val = getReg(rm);
 		reg_t res = rd_val / rm_val;
		setReg(rd, res);
 	} else if (match_LD(ins)) {
 		cout << "LD" << endl;
 		reg_t rd = get_bits(ins, 0, 3);
		reg_t rn = get_bits(ins, 3, 3);
 		reg_t rn_val = getReg(rn);
 		reg_t imm5 = get_bits(ins, 6, 5);

 		reg_t addr = imm5 + rn_val;

 		reg_t res = getMem(addr);
 		setReg(rd, res);
 		log_imm(imm5);
  	} else if (match_B(ins)) {
  		reg_t imm11 = get_bits(ins, 0, 11);
		cout << "B" << endl;
		good = false;
  		int16_t imm = static_cast<int16_t>(imm11);
  		imm = imm << (XLEN - 11);
  		imm = imm >> (XLEN - 11); // sign extension
  		imm11 = static_cast<reg_t>(imm);

  		PC = PC + imm11 - 1;
  		log_imm(imm11);
 	} else if (match_BL(ins)) {
 		cout << "BL" << endl;
 		reg_t imm6 = get_bits(ins, 0, 6);

  		int16_t imm = static_cast<int16_t>(imm6);
  		imm = imm << (XLEN - 6);
  		imm = imm >> (XLEN - 6); // sign extension
  		imm6 = static_cast<reg_t>(imm);
  		
  		setReg(14, PC + 1);
  		PC = PC + imm6 - 1;
  		log_imm(imm6);
 	} else if (match_BX(ins)) {
 		cout << "BX" << endl;
 		reg_t rm = get_bits(ins, 3, 4);
 		reg_t rm_val = getReg(rm);
 		PC = rm_val - 1;
 	} else if (match_NOOP(ins)){
 		good = false;
 		cout << "NOOP" << endl;
 	} else if (match_BCOND(ins)) {
 		cout << "BCOND" << endl;
 		reg_t imm8 = get_bits(ins, 0, 8);
 		reg_t cond = get_bits(ins, 8, 4);
  		int16_t imm = static_cast<int16_t>(imm8);
  		imm = imm << (XLEN - 8);
  		imm = imm >> (XLEN - 8); // sign extension
  		imm8 = static_cast<reg_t>(imm);	
  		reg_t pc_redirect = PC + imm8 - 1;

  		bool br_taken = (cond == EQ && Z)
 					 || (cond == NE && !Z)
 					 || (cond == CS && C)
 					 || (cond == CC && !C)
 					 || (cond == MI && N)
 					 || (cond == PL && !N)
 					 || (cond == VS && V)
 					 || (cond == VC && !V)
 					 || (cond == HI && C && !Z)
 					 || (cond == LS && (!C || Z))
 					 || (cond == GE && (N == V))
 					 || (cond == LT && ((!N) == V))
 					 || (cond == GT && (!Z && (N == V)))
 					 || (cond == LE && (Z || ((!N) == V)))
 					 || (cond == AL);

  		PC = (br_taken) ? pc_redirect : PC;
  		log_imm(imm8);
 	} else if (ins == 0x0000){
 		cout << "Program stopped" << endl;
 		exit(0);
 	} else {
 		// should not reach here expections
 		cerr << "Unrecognized op code at PC " << PC  << endl;
 		cerr << hex << ins << endl;
 		exit(1);
 	}
 	PC = PC + 1;
 	if (trace && good)
 		printTrace();
 	if (good)
 		printLog();
 }

reg_t Processor::add(reg_t op1, reg_t op2) {
	return add(op1, op2, true);
}

reg_t Processor::add(reg_t op1, reg_t op2, bool flag) {
	uint32_t val1 = static_cast<uint32_t>(op1);
	uint32_t val2 = static_cast<uint32_t>(op2);

	uint32_t res = val1 + val2;
	if (flag) {
		// flag setting
		C = (res >> (XLEN - 1)) & 0x1;
		V = ((res >> (XLEN - 2)) & 0x1) ^ C;
	}
	return res;
}

reg_t Processor::sub(reg_t op1, reg_t op2, bool flag) {
	op2 = ~op2 + 1;
	return add(op1, op2, flag);
}

reg_t Processor::sub(reg_t op1, reg_t op2) {
	op2 = ~op2 + 1;
	return add(op1, op2);
}