//
// Created by aaron on 12/29/2017.
//

#include <iostream>
#include <sstream>
#include <vector>
#include "Bot.h"
#include "Assembly.h"
#include "../../../flags.h"
#include "../../World.h"

#if IOBOTS_DEBUG
#include "Assembler.h"
#endif

namespace IOBots{
	Bot::Bot(int memSize) {
		mem = new uint8_t[memSize] {0};
		this->memSize = memSize;
		this->SP = static_cast<uint16_t>(memSize - 1);
	}

	Bot::~Bot() {
		delete mem;
	}

	void Bot::setMemWord(int loc, uint16_t set) {
		if(loc < memSize) {
			mem[loc] = static_cast<uint8_t>(set & 0xFF);
			mem[loc + 1] = static_cast<uint8_t>((set & 0xFF00) >> 8);
		}
	}

	uint16_t Bot::getMemWord(int loc) {
		if(loc < memSize)
			return mem[loc] + (static_cast<uint16_t>(mem[loc+1]) << 8);
		return 0x0;
	}

	int Bot::getMemSize() {
		return memSize;
	}

	void Bot::step() {
		Instruction instruction{
				mem[PC],
				NUM_OPERANDS[mem[PC]],
				Operand(),
				Operand()
		};

		if(instruction.opcode > sizeof(OPCODES) / sizeof(OPCODES[0]))
			throw std::runtime_error("Invalid opcode "+std::to_string(instruction.opcode));

		//Pointer to the byte at the end of the instruction
		uint16_t valuePointer = PC + (uint16_t)1;

		//Has at least one operand
		if(instruction.numOperands > 0){
			instruction.a.type = static_cast<OperandType>(mem[PC + 1] & 0x0F);
			if(instruction.a.hasValue()){
				valuePointer += 2;
				instruction.a.value = getMemWord(valuePointer-1);
			}
		}
		//Has two operands
		if(instruction.numOperands == 2){
			instruction.b.type = static_cast<OperandType>((mem[PC+1] & 0xF0) >> 4);
			if(instruction.b.hasValue()){
				valuePointer += 2;
				instruction.b.value = getMemWord(valuePointer-1);
			}
		}

#if IOBOTS_DEBUG

		std::cout
				<< std::hex
				<< Assembler::INSTRUCTIONS[instruction.opcode]
				<< " [0x" << instruction.a.type
				<< ":0x" << instruction.a.value
				<< ", 0x" << instruction.b.type
				<< ":0x" << instruction.b.value
				<< "] @ 0x" << PC
				<< std::endl;

#endif

		PC = valuePointer + (uint16_t)1;

		//Execute the instruction
		OPCODES[instruction.opcode](*this, instruction);
	}

	void Bot::tick() {
		if(!HF)
			step();
	}

	bool Bot::loadProgram(std::vector<uint8_t> &prog) {
		if(prog.size() > memSize - PROG_OFFSET) return false;
		for(int i = 0; i < prog.size(); i++)
			mem[i+PROG_OFFSET] = prog[i];
		return true;
	}

	void Bot::interrupt(uint16_t interrupt) {
		//If insead of switch for separate scopes
		if(interrupt == 0x0) { //Print debug info
			std::cout << this << std::endl;
		}else if(interrupt == 0x1){ /**TODO Hardware Query**/ }
		else if(interrupt == 0x2){ //TODO Move
			auto h = static_cast<Heading>(A);
			if(NORTH <= h <= WEST && h != heading){
				heading = h;
				energy -= ENERGY_ROT;
			}
			move(B);
		}
	}

	uint16_t Bot::move(uint16_t steps) {
		if(steps > energy / ENERGY_MOVE)
			steps = energy / ENERGY_MOVE;
		switch(heading){
			case NORTH:
				pos.y += steps;
				break;
			case EAST:
				pos.x += steps;
				break;
			case SOUTH:
				pos.y -= steps;
				break;
			case WEST:
				pos.x -= steps;
				break;
		}
		energy -= steps * ENERGY_MOVE;
		return steps;
	}

	std::ostream& operator<<(std::ostream& os, Bot& bot){
		return os
				<< std::dec
				<< "Bot@(" << bot.pos.x << "," << bot.pos.y << "):"
				<< "\n\t" << bot.getMemSize() << " bytes mem"
				<< "\n\t" << bot.energy << " energy"
				<< std::hex
				<< "\n\tA  = 0x" << bot.A
				<< "\n\tB  = 0x" << bot.B
				<< "\n\tC  = 0x" << bot.C
				<< "\n\tD  = 0x" << bot.D
				<< "\n\tPC = 0x" << bot.PC
				<< "\n\tSP = 0x" << bot.SP;
	}
}
