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

    game->setGraphics(graphics);
    graphics->initSDL();
    graphics->initGraphics();

    while (!game->isGameOver()) {
        graphics->frameStart();

        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                game->exit();
            }
            game->handleEvent(e);
        }

        graphics->clearScreen();
        game->update();
        game->draw();

        graphics->frameEnd();
    }

    delete graphics;
    delete game;

    return 0;
}
