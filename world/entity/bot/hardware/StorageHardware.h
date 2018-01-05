//
// Created by Aaron on 1/4/18.
//

#ifndef IOBOTS_STORAGEHARDWARE_H
#define IOBOTS_STORAGEHARDWARE_H

#include "Hardware.h"

namespace IOBots::Hardware{
	class StorageHardware: public Hardware{
	private:
		int memSize;
	public:
		uint8_t* mem;

		explicit StorageHardware(int memSize);
		StorageHardware() = delete;
		~StorageHardware();

		uint8_t getHardwareID() override;
		void interrupt() override;

		void setMemWord(int loc, uint16_t set);
		uint16_t getMemWord(int loc);
	};

}


#endif //IOBOTS_STORAGEHARDWARE_H
