#include <iostream>
#include <cstdlib>
#include <ctime>

#include "inc/Game.hpp"
#include "inc/Graphics.hpp"

int main() {
	srand(time(0));
	
	Game* game;
	Graphics* graphics;

	game = new Game();
	graphics = new Graphics();

	graphics->initSDL();
	graphics->initGraphics();
	game->setGraphics(graphics);

	game->finishInitialization();

	game->gameLoopMainMenu();

	debug("cleaning up");
	delete graphics;
	delete game;

	return 0;
}
