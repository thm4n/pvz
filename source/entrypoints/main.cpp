#include <iostream>
#include <cstdlib>
#include <ctime>

#include "inc/Game.hpp"
#include "inc/Graphics.hpp"

int main() {
	srand(time(0));
	SDL_Event e;
	
	Game* game;
	Graphics* graphics;

	game = new Game();
	graphics = new Graphics();

	graphics->initSDL();
	graphics->initGraphics();
	game->setGraphics(graphics);

	while(!game->isGameOver()) {
		graphics->frameStart();

		if(SDL_PollEvent(&e) != 0) {
			// User requests quit
			if(e.type == SDL_QUIT) {
				info("User requested quit");
				game->exit();
			}
			game->handleEvent(e);
		}

		graphics->clearScreen();
		game->update();
		game->draw();

		SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
		graphics->frameEnd();
	}
	info("Game loop ended");

	debug("cleaning up");
	delete graphics;
	delete game;

	return 0;
}
