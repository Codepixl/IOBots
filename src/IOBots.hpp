#ifndef IOBOTS_IOBOTS_HPP
#define IOBOTS_IOBOTS_HPP

#include "world/bot/Bot.hpp"
#include "graphics/Renderer.hpp"
#include <SDL2/SDL.h>
#include <ctime>

#define BOT_TICK_TIMESTEP 0.001

class IOBots {
public:
	static Renderer renderer;
	static Bot bot;
	static double deltaTime;
	static void start();
private:
	static bool pollEvents(); //Returns false if the game should quit
	static void loop();
};

#endif //IOBOTS_IOBOTS_HPP