//
// Created by Aaron on 1/4/18.
//

#include <iostream>
#include <cstring>
#include "StorageHardware.hpp"
#include "../Bot.hpp"

uint8_t StorageHardware::getHardwareID(){
	return STORAGE_HWID;
}

StorageHardware::StorageHardware(int memSize){
	mem = new uint8_t[memSize];
	this->memSize = memSize;
}

StorageHardware::StorageHardware(uint8_t *buffer, size_t buffer_size) {
    this->deserialize(buffer, buffer_size);
}

StorageHardware::~StorageHardware(){
	delete mem;
}

void StorageHardware::setMemWord(int loc, uint16_t set) {
	if(loc < memSize) {
		mem[loc] = static_cast<uint8_t>(set & 0xFF);
		mem[loc + 1] = static_cast<uint8_t>((set & 0xFF00) >> 8);
	}
}

uint16_t StorageHardware::getMemWord(int loc) {
	if(loc < memSize)
		return mem[loc] + (static_cast<uint16_t>(mem[loc+1]) << 8);
	return 0x0;
}

void StorageHardware::interrupt(){
	switch(attachedBot->A){
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
            break;
		}
		case 3:{//Write many
			uint16_t wordCount = attachedBot->pop();
			uint16_t loc = attachedBot->pop();
			uint16_t botLoc = attachedBot->pop();
			for(int i = 0; i < wordCount; i++){
				setMemWord(loc + i * 2, attachedBot->getMemWord(botLoc + i * 2));
			}
            break;
		}
		default:{ break; }
	}
}

bool StorageHardware::deserialize(uint8_t *buffer, size_t buffer_size) {
    auto* header = (HARDWARE_HEADER*) buffer;
    this->memSize = header->size - sizeof(HARDWARE_HEADER);
    this->mem = new uint8_t[this->memSize];
	return true;
}

void StorageHardware::serialize(uint8_t *buffer) {
    Hardware::serialize(buffer);
    buffer += sizeof(HARDWARE_HEADER);
    memcpy(buffer, this->mem, this->memSize);
}

size_t StorageHardware::calculateSerializedSize() {
    return sizeof(HARDWARE_HEADER) + this->memSize;
}
