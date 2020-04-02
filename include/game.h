#ifndef IOBOTS_GAME_H
#define IOBOTS_GAME_H

#include <world/bot/Bot.h>

#define BOT_TICK_TIMESTEP 0.001

namespace IOBots {
	extern Bot bot;
	extern double deltaTime;
	void start();
	bool pollEvents(); //Returns false if the game should quit
	void loop();
}

#endif //IOBOTS_GAME_H