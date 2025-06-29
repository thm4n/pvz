#include "inc/Game.hpp"

Game::Game() {
	debug("Creating Game class");
	this->_exit = false;
	this->_stateManager = new StateManager();
	debug("Game class created");
}

Game::~Game() {
    debug("Destroying Game class");

	debug("Destroying StateManager");
	delete (this->_stateManager);

	debug("clear events");
	SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    
	debug("Game class destroyed");
}

void Game::destroyResourceManager() {
	if(this->_resourceManager) {
		debug("Destroying ResourceManager");
		delete this->_resourceManager;
		this->_resourceManager = nullptr;
	}
}

void Game::handleEvent(SDL_Event& e) {
    switch (e.type) {
        case SDL_KEYDOWN:
			info("Key pressed");
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                this->exit();
            }
            break;
        case SDL_KEYUP:
			info("Key released");
            break;
        case SDL_MOUSEMOTION:
            break;
        case SDL_MOUSEBUTTONDOWN:
			info("Mouse button pressed");
            break;
        case SDL_MOUSEBUTTONUP:
			info("Mouse button released");
            break;
        case SDL_MOUSEWHEEL:
			info("Mouse wheel scrolled");
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
    if (this->_exit) {
		info("Game Over");
		return true;
	}
	return false;
}

void Game::exit() {
	switch(this->_stateManager->getState()) {
	case GameState::MainMenu:
		debug("Exiting Main Menu");
		this->_stateManager->setState(GameState::Exit);
		break;
	case GameState::InGame:
		debug("Exiting In Game");
		this->_stateManager->setState(GameState::MainMenu);
		break;
	default:
		debug("Exiting from %s state: %s", this->_stateManager->getStateName(), this->_stateManager->getStateName(GameState::Exit));
		this->_stateManager->setState(GameState::Exit);
		break;
	}
}

void Game::setGraphics(Graphics* graphics) {
    debug("Setting Graphics");
    this->_graphics = graphics;

    debug("Creating ResourceManager");
    this->_resourceManager = graphics->createResourceManager();
    if (!this->_resourceManager) {
        error("Failed to create ResourceManager");
        throw std::runtime_error("Failed to create ResourceManager");
    } else {
        debug("ResourceManager created successfully");
    }
}

void Game::gameLoopMainMenu() {
	SDL_Event e;

	debug("Enetring Main Menu Loop");
	this->_stateManager->setState(GameState::MainMenu);

	fs::path selector_screen_reanim_file_path = "resources/reanims/SelectorScreen.reanim";
	if (!fs::exists(selector_screen_reanim_file_path)) {
		error("Selector screen reanim file does not exist: %s", selector_screen_reanim_file_path.string().c_str());
		throw std::runtime_error("Selector screen reanim file does not exist");
	}

	Animation* selectorScreenAnimation = this->loadAnimation(selector_screen_reanim_file_path);

	while(this->_stateManager->getState() == GameState::MainMenu) {
		this->_graphics->frameStart();

		while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				info("User requested quit");
				this->exit();
			}
			this->handleEvent(e);
		}

		this->_graphics->clearScreen();
		this->update();
		this->draw();

		SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
		this->_graphics->frameEnd();
	}

	debug("Cleaning up animations");
	delete selectorScreenAnimation;

	debug("Exiting Main Menu Loop");
}

void Game::gameLoopInGame() {
	SDL_Event e;

	debug("Enetring In-Game Loop");
	this->_stateManager->setState(GameState::InGame);

	while(this->_stateManager->getState() == GameState::InGame) {
		this->_graphics->frameStart();

		while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				info("User requested quit");
				this->exit();
			}
			this->handleEvent(e);
		}

		this->_graphics->clearScreen();
		this->update();
		this->draw();

		SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
		this->_graphics->frameEnd();
	}

	debug("Exiting In-Game Loop");
}

void Game::loadResources() {
	this->_stateManager->setState(GameState::LoadingResources);
	
	std::string resourcesFilePath = "resources/resources.json";
	if (!fs::exists(resourcesFilePath)) {
		error("Resources file does not exist: %s", resourcesFilePath.c_str());
		throw std::runtime_error("Resources file does not exist");
	}

	debug("loading resource file: %s", resourcesFilePath.c_str());
	std::ifstream resourceFile(resourcesFilePath, std::ios::in);
	if (!resourceFile.is_open()) {
		error("Failed to open resources file: %s", resourcesFilePath.c_str());
		throw std::runtime_error("Failed to open resources file");
	}
	ordered_json resources = json::parse(resourceFile);
	resourceFile.close();

	debug("Resources file loaded successfully");

	for(uint i = 0; i < resources.size(); i++) {
		debug("Processing resource group: %s", resources[i]["name"].template get<std::string>().c_str());
		auto& resourceGroup = resources[i]["Images"];
		// for(uint j = 0; j < resourceGroup.size(); j++) {
		// 	this->_resourceManager->loadImageResource(
		// 		resourceGroup[j]["id"].template get<std::string>(),
		// 		resourceGroup[j]["path"].template get<std::string>()
		// 	);
		// }

		resourceGroup = resources[i]["Font"];
		for(uint j = 0; j < resourceGroup.size(); j++) {
			this->_resourceManager->loadFontResource(
				resourceGroup[j]["id"].template get<std::string>(),
				resourceGroup[j]["path"].template get<std::string>(),
				resourceGroup[j]["size"].template get<uint>()
			);
		}

		resourceGroup = resources[i]["Sound"];
		for(uint j = 0; j < resourceGroup.size(); j++) {
			this->_resourceManager->loadAudioResource(
				resourceGroup[j]["id"].template get<std::string>(),
				resourceGroup[j]["path"].template get<std::string>()
			);
		}
	}
}

void Game::finishInitialization() {
	debug("Finished Game initialization");
	this->_stateManager->setState(GameState::MainMenu);
	SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

Animation* Game::loadAnimation(const fs::path& reanimFilePath) {
	debug("Loading animation from file: %s", reanimFilePath.string().c_str());
	
	Animation* animation = AnimationReader::readAnimation(reanimFilePath.string());
	if (!animation) {
		error("Failed to load animation from file: %s", reanimFilePath.string().c_str());
		throw std::runtime_error("Failed to load animation");
	}
	return animation;
}