#include <game.h>
#include <SDL2/SDL.h>
#include <graphics/graphics.h>
#include <ctime>

using namespace IOBots;

Bot IOBots::bot(0x10000);
double IOBots::deltaTime = 0.0;

void IOBots::start(){
	timespec startTime, endTime;
	if(Graphics::initGraphics()){
		while(pollEvents()) {
			clock_gettime(CLOCK_REALTIME, &startTime);
			loop();
			clock_gettime(CLOCK_REALTIME, &endTime);
			deltaTime = endTime.tv_sec - startTime.tv_sec + (endTime.tv_nsec - startTime.tv_nsec) / 1000000000.;
		}
		Graphics::cleanupGraphics();
	}
}

bool IOBots::pollEvents(){
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		if(e.type == SDL_QUIT) {
			return false;
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
	Graphics::draw();
}