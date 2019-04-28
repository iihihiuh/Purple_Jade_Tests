#include "encoding.h"
#include "processor.h"
#include <iostream>
#include <string>

using namespace std;

void Usage() {
	cerr << "usage " << " ./spoke <program_name> [options]" << endl;
	cerr << "Options:" << endl;
	cerr << "  -d    debug mode" << endl;
	cerr << "  -t    enable trace" << endl;
	exit(1);
}

int main(int argc, char** argv) {
	if (argc < 2) {
		Usage();
	}

	string filename = string(argv[1]);
	bool debug = false;
	bool trace = false;
	if (argc >= 3) {
		for (int i = 2; i < argc; i++) {
			if (!strcmp(argv[i], "-d")) {
				debug = true;
				continue;
			}

			if (!strcmp(argv[i], "-t")) {
				trace = true;
				continue;
			}

			Usage();
		}
	}

	Processor core = Processor();
	
	core.load_program(filename, (reg_t)0);

	if (debug)	{
		for (std::string line; std::getline(std::cin, line);) {
			if (line == std::string("quit"))
				break;
			core.step(trace);
	    }
	} else {
		core.start(trace);
	}
	return 0;
}