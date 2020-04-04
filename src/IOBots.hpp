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

	///Starts the game.
	static void start();
private:
    ///The main game loop that runs every frame.
    static void loop();

    /**
     * Runs every loop to poll and handle SDL events.
     * @return Returns false if the game should quit.
     */
	static bool pollEvents();
};

#endif //IOBOTS_IOBOTS_HPP