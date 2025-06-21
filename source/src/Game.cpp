#include "inc/Game.hpp"

Game::Game() {
    this->_exit = false;
}

Game::~Game() {
    debug("Destroying Game class");
    delete(this->_resourceManager);
    debug("Game class destroyed");
}

void Game::handleEvent(SDL_Event& e) {
    switch(e.type) {
    case SDL_KEYDOWN:
        if(e.key.keysym.sym == SDLK_ESCAPE) {
            this->exit();
        }
        break;
    case SDL_KEYUP:
        break;
    case SDL_MOUSEMOTION:
        break;
    case SDL_MOUSEBUTTONDOWN:
        break;
    case SDL_MOUSEBUTTONUP:
        break;
    case SDL_MOUSEWHEEL:
        break;
    }
}

void Game::update() {

}

void Game::draw() {
    
    // must be called at end
    this->_graphics->draw();
}

bool Game::isGameOver() {
    if(this->_exit)
        return true;

    for (auto& z : this->_zombies)
        if(z.col <= 0) return true;
    return false;
}

void Game::exit() {
    this->_exit = true;
}

void Game::setGraphics(Graphics* graphics) {
    debug("Setting Graphics");
    this->_graphics = graphics;

    debug("Creating ResourceManager");
    this->_resourceManager = graphics->createResourceManager();
    if(!this->_resourceManager) {
        error("Failed to create ResourceManager");
        // throw std::runtime_error("Failed to create ResourceManager");
    }
    else {
        debug("ResourceManager created successfully");
    }
}
