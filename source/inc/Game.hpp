#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>

#include "Logger.hpp"

#include "Entity.hpp"
#include "Plant.hpp"
#include "Zombie.hpp"

#include "Graphics.hpp"
#include "ResourceManager.hpp"

#define ROWS 5
#define COLS 10

class Game {
private:
    std::vector<Plant> _plants;
    std::vector<Zombie> _zombies;
    bool _exit;
    Graphics* _graphics;
    ResourceManager* _resourceManager;

public:
    Game();
    ~Game();
    
    void handleEvent(SDL_Event& e);

    void update();
    void draw();
    void exit();

    bool isGameOver();
    void setGraphics(Graphics* graphics);
};
