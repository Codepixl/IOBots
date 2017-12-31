#include <iostream>
#include <unordered_map>
#include <fstream>
#include "Bot.h"
#include "Assembly.h"
#include "Assembler.h"


int main(){
	std::vector<uint8_t> out;
	std::ifstream in("../assembly.asm");
	if(in.is_open()){
		IOBot::Assembler::assemble(in, out);
		in.close();
		IOBot::Bot b(0x10000);
		for(int i = 0; i < out.size(); i++)
			b.mem[i] = out[i];
		for(int i = 0; i < 20; i++)
			b.step();
		std::cout << b << std::endl;
	}else{
		std::cout << "File not opened." << std::endl;
	}
	return 0;
}