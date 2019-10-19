//
// Created by Aaron on 1/4/18.
//

#include <world/entity/bot/hardware/Hardware.h>

namespace IOBots::Hardware{
	uint8_t Hardware::getHardwareID(){
		return INVALID_HWID;
	}

	uint8_t Hardware::getAttachedPort(){
		return attachedPort;
	}

	Bot* Hardware::getAttachedBot(){
		return attachedBot;
	}

	void Hardware::setAttachedBot(Bot* bot, uint8_t attachedPort){
		this->attachedBot = bot;
		this->attachedPort = attachedPort;
	}

	void Hardware::interrupt(){

	}

	void Hardware::detach(){
		attachedBot = nullptr;
		attachedPort = 0;
	}
}
