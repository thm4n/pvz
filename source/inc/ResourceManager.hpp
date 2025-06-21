#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <filesystem>
namespace fs = std::filesystem;

#include "Texture.hpp"

#include "Logger.hpp"

class ResourceManager {
public:
	ResourceManager(SDL_Renderer* renderer);

	~ResourceManager();

	// Load a resource from file
	static void loadResource(const std::string& resourcePath);

	static Texture* getResource(const std::string& resourcePath);

private:
	static SDL_Renderer* _renderer; // Ref to the Pointer to the Graphics' SDL renderer
	static std::map<const std::string, Texture*> _textures; // Map of loaded textures
	
	void freeAll();
};
