#ifndef IOBOTS_GRAPHICS_H
#define IOBOTS_GRAPHICS_H

#include <SDL2/SDL.h>

namespace IOBots::Graphics {
	extern SDL_Window* window;
	extern SDL_Surface* screenSurface;
	extern SDL_Renderer* renderer;

	bool initGraphics();
	void cleanupGraphics();
	void draw();
};

#endif //IOBOTS_GRAPHICS_H