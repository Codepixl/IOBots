#include <iostream>
#include <unordered_map>
#include <fstream>
#include <unistd.h>
#include "world/entity/bot/Bot.h"
#include "world/entity/bot/Assembly.h"
#include "world/entity/bot/Assembler.h"


int main(){
	std::vector<uint8_t> out;
	std::ifstream in("../assembly.asm");
	if(in.is_open()){
        std::cout << "Assembling assembly.asm..." << std::endl;
		IOBots::Assembler::assemble(in, out);
		in.close();
		IOBots::Bot b(0x10000);
		b.loadProgram(out);
        std::cout << "Assembled! Running..." << std::endl;
        clock_t start_clock;
        start_clock = clock();
		while(!b.HF)
			b.tick();
        std::cout << "Finished running! (" << clock() - start_clock << " clocks) Final bot state:" << std::endl << b << std::endl;
	}else{
		std::cout << "File not opened." << std::endl;
	}
	return 0;
}
