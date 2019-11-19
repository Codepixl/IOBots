#include <iostream>
#include <unordered_map>
#include <fstream>
#include <world/entity/bot/Bot.h>
#include <world/entity/bot/Assembly.h>
#include <world/entity/bot/Assembler.h>


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

        //Serialize and deserialize bot before running (essentially, make a copy)
        auto *buffer = new uint8_t[b.calculateSerializedSize()];
        b.serialize(buffer);
        auto* deserializedBot = new IOBots::Bot(buffer, b.calculateSerializedSize());

        //Run both bot and deserialized bot
		while(!b.HF)
			b.tick();
		while(!deserializedBot->HF)
		    deserializedBot->tick();

		//Print both bots so we can compare to see if they ended up the same
        std::cout << "Finished running! (" << clock() - start_clock << " host CPU clocks) Final bot state:" << std::endl << b << std::endl;
        std::cout << "Deserialized bot: " << std::endl;
        std::cout << *deserializedBot << std::endl;
	}else{
		std::cout << "File not opened." << std::endl;
	}
	return 0;
}
