#pragma once
#include <SDL2/SDL.h>

#include <cstdlib>
#include <iostream>
#include <exception>
#include <vector>
#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;

#include <json.hpp>
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

#include "Entity.hpp"
#include "Graphics.hpp"
#include "Logger.hpp"
#include "Plant.hpp"
#include "Zombie.hpp"

#include "ResourceManager.hpp"
#include "Animation.hpp"
#include "StateManager.hpp"

#define ROWS 5
#define COLS 10

class Game {
private:
	std::vector<Plant> _plants;
	std::vector<Zombie> _zombies;
	bool _exit;
	Graphics* _graphics;
	ResourceManager* _resourceManager;
	StateManager* _stateManager;

public:
    Game();
    ~Game();
	void destroyResourceManager();
	
    void handleEvent(SDL_Event& e);

    void update();
    void draw();
    void exit();

    bool isGameOver();
    void setGraphics(Graphics* graphics);

	void gameLoopMainMenu();
	void gameLoopInGame();

	void loadResources();
	void finishInitialization();

	Animation* loadAnimation(const fs::path& reanimFilePath);
};
