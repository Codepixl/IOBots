#ifndef IOBOTS_RENDERER_HPP
#define IOBOTS_RENDERER_HPP

#include <SDL2/SDL.h>

class Renderer {
public:
    Renderer();
    ~Renderer();

    ///Start the renderer and open the window.
	bool init();

	///Cleanup SDL and rendering resources.
	void cleanup();

	///Called every frame to draw the game.
	void draw();
private:
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Renderer* renderer = NULL;
};

#endif //IOBOTS_RENDERER_HPP