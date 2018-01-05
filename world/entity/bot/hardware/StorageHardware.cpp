//
// Created by Aaron on 1/4/18.
//

#include <iostream>
#include "StorageHardware.h"
#include "../Bot.h"

uint8_t IOBots::Hardware::StorageHardware::getHardwareID(){
	return 0x1;
}

IOBots::Hardware::StorageHardware::StorageHardware(int memSize){
	mem = new uint8_t[memSize];
	this->memSize = memSize;
}

IOBots::Hardware::StorageHardware::~StorageHardware(){
	delete mem;
}

void IOBots::Hardware::StorageHardware::setMemWord(int loc, uint16_t set) {
	if(loc < memSize) {
		mem[loc] = static_cast<uint8_t>(set & 0xFF);
		mem[loc + 1] = static_cast<uint8_t>((set & 0xFF00) >> 8);
	}
}

uint16_t IOBots::Hardware::StorageHardware::getMemWord(int loc) {
	if(loc < memSize)
		return mem[loc] + (static_cast<uint16_t>(mem[loc+1]) << 8);
	return 0x0;
}

void IOBots::Hardware::StorageHardware::interrupt(){
	switch(attachedBot->B){
		case 0:{//Read
			attachedBot->push(getMemWord(attachedBot->pop()));
			break;
		}
		case 1:{//Write
			uint16_t loc = attachedBot->pop();
			uint16_t word = attachedBot->pop();
			setMemWord(loc, word);
			break;
		}
		case 2:{//Read many
			uint16_t wordCount = attachedBot->pop();
			uint16_t loc = attachedBot->pop();
			uint16_t botLoc = attachedBot->pop();
			for(int i = 0; i < wordCount; i++){
				attachedBot->setMemWord(botLoc + i * 2, getMemWord(loc + i * 2));
			}

		}
		case 3:{//Write many
			uint16_t wordCount = attachedBot->pop();
			uint16_t loc = attachedBot->pop();
			uint16_t botLoc = attachedBot->pop();
			for(int i = 0; i < wordCount; i++){
				setMemWord(loc + i * 2, attachedBot->getMemWord(botLoc + i * 2));
			}
		}
		default:{ break; }
	}
}
