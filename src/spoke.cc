#include "encoding.h"
#include "processor.h"
#include <iostream>
#include <string>

using namespace std;

void Usage() {
	cerr << "usage " << " ./spoke <program_name> [options]" << endl;
	cerr << "Options:" << endl;
	cerr << "  -d    debug mode" << endl;
	exit(1);
}

int main(int argc, char** argv) {
	if (argc < 2) {
		Usage();
	}

	string filename = string(argv[1]);
	bool debug = false;
	if (argc == 3) {
		if (!strcmp(argv[2], "-d")) {
			debug = true;
		} else {
			Usage();
		}
	}

	Processor core = Processor();
	
	core.load_program(filename, (reg_t)0);

	if (debug)	{
		for (std::string line; std::getline(std::cin, line);) {
			if (line == std::string("quit"))
				break;
			core.step();
	    }
	} else {
		core.start();
	}
	return 0;
}