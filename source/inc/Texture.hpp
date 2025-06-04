#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <map>

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Logger.hpp"
#include "Graphics.hpp"

class Graphics;

class Texture {
private:
	static Graphics* _graphics;

	SDL_Texture* _texture;

	int _width;
	int _height;

	std::string _filePath;

public:
	Texture(const std::string& path = "");
	~Texture();

	static void setGraphics(Graphics* graphics);

	void loadFromFile(const std::string& path = "");

	void free();

	void render(int x, int y); // needed?

	int getWidth() const;
	int getHeight() const;
	const std::string& getName() const;
};
