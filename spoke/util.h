#ifndef _UNTIL_H_
#define _UNTIL_H_

#include "processor.h"
#include <iostream>

reg_t get_bits(reg_t val, int start_pos, int length) {
	reg_t mask = (reg_t) - 1;
	mask = ~(mask << length);
	mask = mask << start_pos;
	return (val & mask) >> start_pos;
}

#endif