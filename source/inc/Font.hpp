#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <exception>

#include <filesystem>
namespace fs = std::filesystem;

#include "Logger.hpp"

class Font {
public:
	Font(const std::string& fontPath, uint fontSize);
	~Font();

	void loadFontFile();

	void free();

	uint getSize() const;
	const fs::path& getPath() const;
	TTF_Font* getFont() const;

private:
	uint _size;
	fs::path _path;
	TTF_Font* _font;
};
