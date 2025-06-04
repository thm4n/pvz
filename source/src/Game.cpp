#include "inc/Game.hpp"

Game::Game() {
	this->_exit = false;
	this->_resourceManager = nullptr;
	this->_graphics = nullptr;
}

Game::~Game() {
	debug("destroying Game class");
	if(this->_resourceManager) {
		debug("releasing ResourceManager");
		delete this->_resourceManager;
	}
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

}

bool Game::isGameOver() {
	if (this->_exit)
		return true;

	for (auto& z : this->_zombies)
		if (z.col <= 0) return true;
	return false;
}

void Game::exit() {
	this->_exit = true;
}

void Game::setGraphics(Graphics* graphics) {
	this->_graphics = graphics;
}

void Game::setupResourceManager() {
	if(!this->_graphics) {
		error("cannot setup resource manager without graphics being setup first!");
		return;
	}

	this->_resourceManager = new ResourceManager(this->_graphics);
}
