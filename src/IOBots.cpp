#include <world/bot/hardware/KeyboardHardware.h>
#include "IOBots.hpp"

Bot IOBots::bot(0x10000);
double IOBots::deltaTime = 0;
Renderer IOBots::renderer = Renderer();

void IOBots::start(){
	timespec startTime, endTime;
	if(renderer.init()){
		while(pollEvents()) {
			clock_gettime(CLOCK_REALTIME, &startTime);
			loop();
			clock_gettime(CLOCK_REALTIME, &endTime);
			deltaTime = endTime.tv_sec - startTime.tv_sec + (endTime.tv_nsec - startTime.tv_nsec) / 1000000000.;
		}
		renderer.cleanup();
	}
}

bool IOBots::pollEvents(){
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
		    case SDL_QUIT:
		        return false;
		    case SDL_KEYDOWN:
		        if(bot.getHardware(KEYBOARD_HWID) != nullptr) {
                    ((KeyboardHardware*)bot.getHardware(KEYBOARD_HWID))->addKeypress(e.key.keysym.scancode);
		        }
		}
	}
	return true;
}

double tickTimer = 0;
void IOBots::loop(){
	tickTimer += deltaTime;
	if(tickTimer > BOT_TICK_TIMESTEP) {
		bot.tick();
		tickTimer = 0;
	}
	renderer.draw();
}
