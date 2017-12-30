//
// Created by aaron on 12/29/2017.
//

#ifndef IOBOT_ASSEMBLER_H
#define IOBOT_ASSEMBLER_H

#include "Assembly.h"
#include <iostream>
#include <vector>


namespace IOBot::Assembler{
	void assemble(std::string assembly, std::vector<uint8_t>& out);
	void parseOperand(std::string operandStr, Operand& operand);
	static std::string INSTRUCTIONS[] = { //NOLINT
			"nop", "mov", "jmp"
	};
}


#endif //IOBOT_ASSEMBLER_H
