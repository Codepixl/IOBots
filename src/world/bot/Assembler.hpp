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
    /**
     * Assembles code for the bot.
     * @param in An inputstream where the assembly will be read from.
     * @param out The bytes of the output program.
     */
	void assemble(std::istream& in, std::vector<uint8_t>& out);

	/**
	 * Parses an operand to an assembly instruction.
	 * @param operandStr The operand in assembly code.
	 * @param operand The operand object that the parsed operand should be stored in.
	 * @param labels A map of the labels in the assembly code.
	 * @param secondPass Whether or not this is the second pass over the code, where label positions will be parsed.
	 */
	void parseOperand(std::string& operandStr, Operand& operand,
					  std::unordered_map<std::string, uint16_t>* labels, bool secondPass);

	/**
	 * Parses an operand's number.
	 * @param operandStr The operand.
	 * @param operand The operand object that the parsed operand will be stored in.
	 * @param labels A map of the labels in the assembly code.
	 */
	void parseOperandNum(std::string& operandStr, Operand& operand, std::unordered_map<std::string, uint16_t>* labels);

	///An array of assembly instruction strings.
	extern std::string INSTRUCTIONS[];
};


#endif //IOBOT_ASSEMBLER_H
