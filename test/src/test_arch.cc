#include "test_funcs.h"
#include <iostream>
#include <string>
using namespace std;

#define FU_NUM 8
#define RS_EN 4
#define ROB_EN 64
#define STBUFF_EN 16

void print_ins(string type, string  rd, string r1, string r2, ostream& s=cout) {
	s << type << " " << rd <<  ((rd == "")? "" : ", ") << r1 <<  ((r1 == "")? "" : ", ") << r2 << endl;
}

void print_ls(string type, string rd, string r1, int imm, ostream& s=cout) {
	s << type << " " << rd << ", [" << r1 << ", " << imm << "]" << endl;
}

int main(int argc, char** argv) {
	//  worst dependence
	li(1,0x8000);
	li(3,2);
	for (int i = 0; i < RS_EN; i++)
		print_ins("DIVU", "r1", "r1", "r3");

	for (int i = 0; i < RS_EN; i++)
		print_ins("MULU", "r2", "r2", "r1");

	for (int i = 0; i < RS_EN * 2; i++)
		print_ins("ADDS", "r2", "r1", "0");

	for (int i = 0; i < RS_EN * 2; i++)
		print_ins("ANDS", "r2", "", "r1");

	for (int i = 0; i < RS_EN; i++)
		print_ls("LDR", "r2", "r1", 4);

	// drain ROB
	for (int i = 0; i < ROB_EN; i++)
		cout << "NOOP" << endl;

	// Renaming space check trying to fill ROB
	for (int i = 0; i < RS_EN; i++)
		print_ins("DIVU", "r1", "r1", "r3");

	for (int i = 0; i < RS_EN; i++)
		print_ins("MULU", "r1", "r1", "r3");

	for (int i = 0; i < RS_EN * 2; i++)
		print_ins("ADDS", "r1", "r1", "0");

	for (int i = 0; i < RS_EN * 2; i++)
		print_ins("ANDS", "r1", "", "r1");

	for (int i = 0; i < RS_EN; i++)
		print_ls("LDR", "r1", "r1", 4);

	for (int i = 0; i < RS_EN; i++)
		print_ins("LSLS", "r1", "r1", "r2");

	// drain ROB
	for (int i = 0; i < ROB_EN; i++)
		cout << "NOOP" << endl;

	// stalling on rs full
	for (int i = 0; i < ROB_EN; i++)
		print_ins("ADDS", "r1", "r1", "0");

	// drain ROB
	for (int i = 0; i < ROB_EN; i++)
		cout << "NOOP" << endl;

	// ld st torture
	li(2,0);
	for (int i = 0; i < RS_EN; i++)
		print_ins("DIVU", "r1", "r1", "r3");

	for (int i = 0; i < STBUFF_EN; i++) {
		print_ls("STR", "r1", "r2", 4);
		print_ls("LDR", "r3", "r2", 4);
	}

	// drain ROB
	for (int i = 0; i < ROB_EN; i++)
		cout << "NOOP" << endl;

	// mis branch handling
	li(1,0);
	print_ins("ADDS", "r1", "r1", "0");
	cout << "BEQ NOOP0" << endl;cout << "NOOP" << endl;
	cout << "BEQ NOOP1" << endl;cout << "NOOP" << endl;
	cout << "BEQ NOOP2" << endl;cout << "NOOP" << endl;
	cout << "BEQ NOOP3" << endl;cout << "NOOP" << endl;
	print_ins("ADDS", "r1", "r1", "0");
	cout << "NOOP0: NOOP" << endl;
	cout << "NOOP1: NOOP" << endl;
	cout << "NOOP2: NOOP" << endl;
	cout << "NOOP3: NOOP" << endl;
	li(1,0);
	print_ins("ADDS", "r1", "r1", "0");
	cout << "BNE NOOP4" << endl;cout << "NOOP" << endl;
	cout << "BEQ NOOP5" << endl;cout << "NOOP" << endl;
	cout << "BEQ NOOP6" << endl;cout << "NOOP" << endl;
	cout << "BEQ NOOP7" << endl;cout << "NOOP" << endl;
	print_ins("ADDS", "r1", "r1", "0");
	cout << "NOOP4: NOOP" << endl;
	cout << "NOOP5: NOOP" << endl;
	cout << "NOOP6: NOOP" << endl;
	cout << "NOOP7: NOOP" << endl;
	li(1,0);
	print_ins("ADDS", "r1", "r1", "0");
	cout << "BNE NOOP8" << endl;cout << "NOOP" << endl;
	print_ins("ADDS", "r4", "r6", "0");
	cout << "BNE NOOP9" << endl;cout << "NOOP" << endl;
	print_ins("ADDS", "r3", "r6", "0");
	cout << "BEQ NOOP10" << endl;cout << "NOOP" << endl;
	cout << "BEQ NOOP11" << endl;cout << "NOOP" << endl;
	print_ins("ADDS", "r1", "r1", "0");
	cout << "NOOP8: NOOP" << endl;
	cout << "NOOP9: NOOP" << endl;
	cout << "NOOP10: NOOP" << endl;
	cout << "NOOP11: NOOP" << endl;
	return 0;
}