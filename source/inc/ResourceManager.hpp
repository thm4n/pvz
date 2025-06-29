#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <filesystem>
namespace fs = std::filesystem;

#include "Texture.hpp"
#include "Font.hpp"

#include "Logger.hpp"
#include "ResourceType.hpp"

class ResourceManager {
public:
	ResourceManager(SDL_Renderer* renderer);

	~ResourceManager();

	// Load a resource from file
	static void loadResource(ResourceType& resourceType, const std::string& resourceName, const std::string& resourcePath);
	static void loadImageResource(const std::string& resourceName, const std::string& resourcePath);
	static void loadAudioResource(const std::string& resourceName, const std::string& resourcePath);
	static void loadFontResource(const std::string& resourceName, const std::string& resourcePath, uint size);
	static void loadTextTexture(const std::string& name, const std::string& text, const std::string& font, uint size, SDL_Color color);

	static Texture* getResource(const std::string& resourcePath);
	static Font* getFont(const std::string& resourceName, uint size);
private:
	static SDL_Renderer* _renderer; // Ref to the Pointer to the Graphics' SDL renderer
	static std::map<const std::string, Texture*> _textures; // Map of loaded textures
	static std::map<const std::string, Font*> _fonts; // Map of loaded fonts
	
	void freeAll();
};
