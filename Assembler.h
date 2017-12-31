//
// Created by aaron on 12/29/2017.
//

#ifndef IOBOT_ASSEMBLER_H
#define IOBOT_ASSEMBLER_H

#include "Assembly.h"
#include <iostream>
#include <vector>
#include <unordered_map>

namespace IOBot::Assembler{
	void assemble(std::istream& in, std::vector<uint8_t>& out);
	void parseOperand(std::string operandStr, Operand& operand,
					  std::unordered_map<std::string, uint16_t>* labels, bool secondPass);
	static std::string INSTRUCTIONS[] = { //NOLINT
			"nop", "mov", "jmp", "call", "ret"
	};
}


#endif //IOBOT_ASSEMBLER_H
