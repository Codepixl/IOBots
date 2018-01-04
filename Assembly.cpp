//
// Created by aaron on 12/29/2017.
//

#include <stdexcept>
#include <iostream>
#include "Assembly.h"
#include "Util.h"
#include "flags.h"

namespace IOBot {
	/////////////
	///Operand///
	/////////////

	uint16_t Operand::get(Bot& bot) {
		switch(type){
			case NONE: throw std::runtime_error("Attempted to get NONE operand!");
			case A: return bot.A;
			case B: return bot.B;
			case C: return bot.C;
			case D: return bot.D;
			case AP: return bot.getMemWord(bot.A);
			case BP: return bot.getMemWord(bot.B);
			case CP: return bot.getMemWord(bot.C);
			case DP: return bot.getMemWord(bot.D);
			case IM: return value;
			case IMP: return bot.getMemWord(value);
			case AIM: return bot.getMemWord(bot.A + value);
			case BIM: return bot.getMemWord(bot.B + value);
			case CIM: return bot.getMemWord(bot.C + value);
			case DIM: return bot.getMemWord(bot.D + value);
			case INVALID: throw std::runtime_error("Attempted to get INVALID operand!");
		}
	}

	void Operand::set(Bot& bot, uint16_t to) {
		switch(type){
			case NONE: throw std::runtime_error("Attempted to set NONE operand!");
			case A: bot.A = to; break;
			case B: bot.B = to; break;
			case C: bot.C = to; break;
			case D: bot.D = to; break;
			case AP: bot.setMemWord(bot.A, to); break;
			case BP: bot.setMemWord(bot.B, to); break;
			case CP: bot.setMemWord(bot.C, to); break;
			case DP: bot.setMemWord(bot.D, to); break;
			case IM: throw std::runtime_error("Attempted to set immediate value operand!");
			case IMP: bot.setMemWord(value, to); break;
			case AIM: bot.setMemWord(bot.A + value, to); break;
			case BIM: bot.setMemWord(bot.B + value, to); break;
			case CIM: bot.setMemWord(bot.C + value, to); break;
			case DIM: bot.setMemWord(bot.D + value, to); break;
			case INVALID: throw std::runtime_error("Attempted to set INVALID operand!");
		}
	}

	bool Operand::hasValue() {
		return type >= IM;
	}

	namespace Instructions{
		void nop(Bot& bot, Instruction& instruction){}

		void mov(Bot& bot, Instruction& instruction){
			instruction.a.set(bot, instruction.b.get(bot));
		}

		void jmp(Bot& bot, Instruction& instruction){
			bot.PC = instruction.a.get(bot);
		}

		void call(Bot& bot, Instruction& instruction){
			bot.SP -= 2;
			bot.setMemWord(bot.SP, bot.PC);
			bot.PC = instruction.a.get(bot);
		}

		void ret(Bot& bot, Instruction& instruction){
			bot.PC = bot.getMemWord(bot.SP);
			bot.SP += 2;
		}

		void add(Bot &bot, Instruction &instruction) {
			uint32_t a = instruction.a.get(bot);
			uint32_t b = instruction.b.get(bot);
			uint32_t res = a + b;
			bot.CF = Util::checkCF(res);
			bot.OF = (a >> 15) == (b >> 15) && (a >> 15) != (res >> 15);
			bot.ZF = Util::checkZF(static_cast<uint16_t>(res));
			bot.SF = Util::checkSF(static_cast<uint16_t>(res));
			instruction.a.set(bot, static_cast<uint16_t>(res));
		}

		void sub(Bot &bot, Instruction &instruction) {
			uint32_t a = instruction.a.get(bot);
			uint32_t b = instruction.b.get(bot);
			uint32_t res = a - b;
			bot.CF = Util::checkCF(res);
			bot.OF = (a >> 15) != (b >> 15) && (a >> 15) != (res >> 15);
			bot.ZF = Util::checkZF(static_cast<uint16_t>(res));
			bot.SF = Util::checkSF(static_cast<uint16_t>(res));
			instruction.a.set(bot, static_cast<uint16_t>(res));
		}

		void mul(Bot &bot, Instruction &instruction) {
			uint32_t a = instruction.a.get(bot);
			uint32_t b = instruction.b.get(bot);
			uint32_t res = a * b;
			bot.CF = Util::checkCF(res);
			bot.OF = (a >> 15) == (b >> 15) && (a >> 15) != (res >> 15);
			bot.ZF = Util::checkZF(static_cast<uint16_t>(res));
			bot.SF = Util::checkSF(static_cast<uint16_t>(res));
			instruction.a.set(bot, static_cast<uint16_t>(res));
		}

		void div(Bot &bot, Instruction &instruction) {
			uint32_t a = instruction.a.get(bot);
			uint32_t b = instruction.b.get(bot);
			uint32_t res = a / b;
			bot.CF = Util::checkCF(res);
			bot.OF = (a >> 15) != (b >> 15) && (a >> 15) != (res >> 15);
			bot.ZF = Util::checkZF(static_cast<uint16_t>(res));
			bot.SF = Util::checkSF(static_cast<uint16_t>(res));
			instruction.a.set(bot, static_cast<uint16_t>(res));
		}

		void shl(Bot &bot, Instruction &instruction) {
			uint32_t a = instruction.a.get(bot);
			uint32_t b = instruction.b.get(bot);
			uint32_t res = a << b;
			bot.CF = static_cast<bool>(res >> 16);
			bot.OF = Util::checkSF(static_cast<uint16_t>(a)) != Util::checkSF(static_cast<uint16_t>(res));
			bot.ZF = Util::checkZF(static_cast<uint16_t>(res));
			bot.SF = Util::checkSF(static_cast<uint16_t>(res));
			instruction.a.set(bot, static_cast<uint16_t>(res));
		}

		void shr(Bot &bot, Instruction &instruction) {
			uint32_t a = instruction.a.get(bot);
			uint32_t b = instruction.b.get(bot);
			uint32_t res = a >> b;
			bot.CF = static_cast<bool>(((a << 16) >> b) & 0x8000);
			bot.OF = bot.OF | (Util::checkSF(static_cast<uint16_t>(a)) != Util::checkSF(static_cast<uint16_t>(res)));
			bot.ZF = Util::checkZF(static_cast<uint16_t>(res));
			bot.SF = Util::checkSF(static_cast<uint16_t>(res));
			instruction.a.set(bot, static_cast<uint16_t>(res));
		}

		void _and(Bot &bot, Instruction &instruction) {
			uint16_t res = instruction.a.get(bot) & instruction.b.get(bot);
			bot.CF = false;
			bot.OF = false;
			bot.ZF = Util::checkZF(res);
			bot.SF = Util::checkSF(res);
			instruction.a.set(bot, res);
		}

		void _or(Bot &bot, Instruction &instruction) {
			uint16_t res = instruction.a.get(bot) | instruction.b.get(bot);
			bot.CF = false;
			bot.OF = false;
			bot.ZF = Util::checkZF(res);
			bot.SF = Util::checkSF(res);
			instruction.a.set(bot, res);
		}

		void _xor(Bot &bot, Instruction &instruction) {
			uint16_t res = instruction.a.get(bot) ^ instruction.b.get(bot);
			bot.CF = false;
			bot.OF = false;
			bot.ZF = Util::checkZF(res);
			bot.SF = Util::checkSF(res);
			instruction.a.set(bot, res);
		}

		void _not(Bot &bot, Instruction &instruction) {
			instruction.a.set(bot, ~instruction.a.get(bot));
		}

		void cmp(Bot &bot, Instruction &instruction) {
			uint32_t a = instruction.a.get(bot);
			uint32_t b = instruction.b.get(bot);
			uint32_t res = a - b;
			bot.CF = Util::checkCF(res);
			bot.OF = (a >> 15) != (b >> 15) && (a >> 15) != (res >> 15);
			bot.ZF = Util::checkZF(static_cast<uint16_t>(res));
			bot.SF = Util::checkSF(static_cast<uint16_t>(res));
		}

		void jz(Bot &bot, Instruction &instruction) {
			if(bot.ZF)
				bot.PC = instruction.a.get(bot);
		}

		void jnz(Bot &bot, Instruction &instruction) {
			if(!bot.ZF)
				bot.PC = instruction.a.get(bot);
		}

		void jl(Bot &bot, Instruction &instruction) {
			if(bot.SF != bot.OF)
				bot.PC = instruction.a.get(bot);
		}

		void jle(Bot &bot, Instruction &instruction) {
			if(bot.SF != bot.OF || bot.ZF)
				bot.PC = instruction.a.get(bot);
		}

		void jg(Bot &bot, Instruction &instruction) {
			if(bot.SF == bot.OF && !bot.ZF)
				bot.PC = instruction.a.get(bot);
		}

		void jge(Bot &bot, Instruction &instruction) {
			if(bot.SF == bot.OF)
				bot.PC = instruction.a.get(bot);
		}

		void _int(Bot &bot, Instruction &instruction) {
#if IOBOTS_DEBUG
			std::cout << "Interrupt 0x" << std::hex << instruction.a.get(bot) << std::endl;
#endif
			switch(instruction.a.get(bot)){
				case 0x0:
				std::cout << bot << std::endl;
					break;
				default: break;
			}
		}

		void push(Bot &bot, Instruction &instruction) {
			bot.SP -= 2;
			bot.setMemWord(bot.SP, instruction.a.get(bot));
		}

		void pop(Bot &bot, Instruction &instruction) {
			instruction.a.set(bot, bot.getMemWord(bot.SP));
			bot.SP += 2;
		}

		void hlt(Bot &bot, Instruction &instruction) {
			bot.HF = true;
		}
	}
}