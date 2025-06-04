#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <map>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Logger.hpp"
#include "Graphics.hpp"
#include "Texture.hpp"

#define ROWS 5
#define COLS 10

class Texture;
class Graphics;

class ResourceManager {
private:
	std::vector<Texture*> _textures;
	Graphics* _graphics;

public:
	ResourceManager(Graphics* graphics);
	~ResourceManager();

	void loadResource(std::string name);
	void freeResource(Texture* resource);
};
