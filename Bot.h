//
// Created by aaron on 12/29/2017.
//

#ifndef IOBOT_BOT_H
#define IOBOT_BOT_H

#define PROG_OFFSET 0x400

namespace IOBot {
	/**
	 * A code-running CPU, Memory, and peripherals that (will be) placed in the world.
	 *
	 * The bot's CPU has 4 16-bit general purpose registers, plus a 16-bit program counter and stack pointer.
	 * Memory is manipulated at the word level with the mov instruction.
	 *
	 * An instruction consists of one byte which is the opcode.
	 * If there are more than one operands for that instruction, it is followed by one byte describing the operands.
	 * - The low 4 bits of that describe the first operand, and the high 4 describe the second.
	 *
	 * Basically, the anatomy of an assembled instruction is as follows (one parenthesis set indicates one byte):
	 * (Opcode) (Operand Descriptor, optional) (Operand 1 value, optional) (Operand 2 value, optional)
	 * So, an instruction can be 1, 2, 4, or 6 bytes long.
	 */
	class Bot {
	private:
		int memSize;
	public:
		uint16_t A = 0;
		uint16_t B = 0;
		uint16_t C = 0;
		uint16_t D = 0;
		uint16_t PC = PROG_OFFSET;
		uint16_t SP = 0;
		bool CF = false; //Carry flag
		bool ZF = false; //Zero flag
		bool SF = false; //Sign flag
		bool OF = false; //Overflow flag
		bool HF = false;
		uint8_t *mem;

		/**
		 * Makes a new bot.
		 * @param memSize The size of the memory. Max is 65536 bytes.
		 */
		explicit Bot(int memSize);

		//Delete the default constructor
		Bot() = delete;

		/**
		 * Frees up the bot's resources for use.
		 */
		~Bot();

		/**
		 * Sets a word in memory.
		 * @param loc The location in memory where the low byte will be.
		 * @param set The word to store in memory.
		 */
		void setMemWord(int loc, uint16_t set);

		/**
		 * Gets a word in memory.
		 * @param loc The location in memory where the low byte will be.
		 * @return The word stored at that location.
		 */
		uint16_t getMemWord(int loc);

		/**
		 * Gets the memory size of the bot.
		 * @return The memory size of the bot.
		 */
		int getMemSize();

		/**
		 * Executes the opcode at the current program counter.
		 *
		 * As of now, every instruction is only one cycle.
		 */
		void step();

		/**
		 * Ticks the robot in the game world.
		 *
		 * This usually entails stepping the program (if !HF), and updating the robot's other things.
		 */
		void tick();

		/**
		 * Loads a program into memory. The program must fit into memory.
		 * @param prog A vector of bytes containing the program.
		 * @return Whether or not the program was successfully loaded.
		 */
		bool loadProgram(std::vector<uint8_t>& prog);
	};

	std::ostream& operator<<(std::ostream& os, Bot& bot);
}

#endif //IOBOT_BOT_H
