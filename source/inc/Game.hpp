#pragma once
#include <SDL2/SDL.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "Entity.hpp"
#include "Graphics.hpp"
#include "Logger.hpp"
#include "Plant.hpp"
#include "ResourceManager.hpp"
#include "Zombie.hpp"

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
