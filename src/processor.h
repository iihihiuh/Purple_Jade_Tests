#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <cstdint>
#include <string>

#define REGNUM 13
#define REGMAX 16

#define XLEN 16

typedef uint16_t reg_t;

class Processor { 
 public:
 	Processor();
 	~Processor();

 	reg_t getReg(reg_t);
 	void setReg(reg_t, reg_t);
 	void load_program(std::string, reg_t);
 	void start(bool);

private:
 	reg_t* regfile;
 	char* data_mem;
 	reg_t* instr_mem;
 	reg_t SP, LR, PC;
 	uint64_t inst_num;
}; // class processor

#endif