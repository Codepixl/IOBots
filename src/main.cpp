#include <iostream>
#include <unordered_map>
#include <fstream>
#include "world/bot/Bot.hpp"
#include "world/bot/Assembly.hpp"
#include "world/bot/Assembler.hpp"
#include "IOBots.hpp"


int main(int argc, char* argv[]){
	if(argc < 2){
		std::cout << "Usage: " << argv[0] << " file.asm" << std::endl;
		return 1;
	}

	std::vector<uint8_t> out;
	std::ifstream in(argv[1]);
		
	if(in.is_open()){
        std::cout << "Assembling assembly.asm..." << std::endl;
		Assembler::assemble(in, out);
		in.close();
		IOBots::bot.loadProgram(out);
        std::cout << "Assembled! Starting game..." << std::endl;
	}else{
		std::cout << "Could not open file " << argv[1] << "." << std::endl;
	}

	IOBots::start();

	return 0;
}
