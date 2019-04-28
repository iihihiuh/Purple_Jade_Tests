#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <cstdint>
#include <string>

#define REGNUM 13
#define REGMAX 16

#define XLEN 16

typedef uint16_t reg_t;

typedef struct {
	reg_t pc;

	bool rs1_read;
	reg_t rs1;
	reg_t rs1_val;

	bool rs2_read;
	reg_t rs2;
	reg_t rs2_val;

	bool rd_write;
	reg_t rd;
	reg_t rd_val;

	bool mem_access;
	bool lors;
	reg_t addr;
	reg_t mem_val;

	bool imm_read;
	reg_t imm_val;
} log_t;

class Processor { 
 public:
 	Processor();
 	~Processor();
	// flags
 	bool N, Z, C, V;

 	reg_t getReg(reg_t);
 	void setReg(reg_t, reg_t);
 	void load_program(std::string, reg_t);
 	void start(bool);
 	void step(bool);
 	reg_t getMem(reg_t addr);
 	void setMem(reg_t addr, reg_t val);
 	void printLog();


private:
	log_t log;
 	reg_t* regfile;
 	reg_t* data_mem;
 	reg_t* instr_mem;
 	reg_t SP, LR, PC;
 	uint64_t inst_num;

 	// private functions
 	// set and log flags
 	void setFlagNZ(reg_t val);
	// loging imm
 	void log_imm(reg_t val) {
 		log.imm_read = true;
 		log.imm_val = val;
	}

	// adds and sub
	reg_t add(reg_t, reg_t);
	reg_t add(reg_t, reg_t, bool);
	reg_t sub(reg_t, reg_t);
	reg_t sub(reg_t, reg_t, bool);
	void printTrace();
}; // class processor

#endif