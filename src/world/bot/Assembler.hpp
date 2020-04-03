//
// Created by aaron on 12/29/2017.
//

#ifndef IOBOTS_ASSEMBLER_H
#define IOBOTS_ASSEMBLER_H

#include "Assembly.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>

class Operand;

namespace Assembler {
	void assemble(std::istream& in, std::vector<uint8_t>& out);
	void parseOperand(std::string& operandStr, Operand& operand,
					  std::unordered_map<std::string, uint16_t>* labels, bool secondPass);
	void parseOperandNum(std::string& operandStr, Operand& operand, std::unordered_map<std::string, uint16_t>* labels);
	extern std::string INSTRUCTIONS[];
};


#endif //IOBOT_ASSEMBLER_H
