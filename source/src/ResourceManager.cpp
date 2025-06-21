#include "inc/ResourceManager.hpp"

SDL_Renderer* ResourceManager::_renderer = nullptr;
std::map<const std::string, Texture*> ResourceManager::_textures = std::map<const std::string, Texture*>();

ResourceManager::ResourceManager(SDL_Renderer* renderer) {
	if(ResourceManager::_renderer || !ResourceManager::_textures.empty()) {
		error("ResourceManager already initialized");
		// throw std::runtime_error("ResourceManager already initialized");
	}
	if(!renderer) {
		error("Renderer cannot be null");
		// throw std::runtime_error("Renderer cannot be null");
	}
	ResourceManager::_renderer = renderer;
}

ResourceManager::~ResourceManager() {
	ResourceManager::_renderer = nullptr;
	ResourceManager::freeAll();
}

// Load a resource from file
void ResourceManager::loadResource(const std::string& resourcePath) {
	debug("%s - Loading resource", resourcePath.c_str());
	if(ResourceManager::getResource(resourcePath)) {
		error("%s - Resource already loaded", resourcePath.c_str());
		// throw std::runtime_error("Resource already loaded");
	}

	Texture* texture = new Texture();
	texture->loadFromFile(ResourceManager::_renderer, resourcePath);
	ResourceManager::_textures.insert({resourcePath, texture});
	debug("%s - Resource loaded", resourcePath.c_str());
}

Texture* ResourceManager::getResource(const std::string& resourcePath) {
	auto it = ResourceManager::_textures.find(resourcePath);
	if(it != ResourceManager::_textures.end())
		return it->second;
	return nullptr;
}

void ResourceManager::freeAll() {
	debug("freeing all resources:");
	if(auto& pair : ResourceManager::_textures) {
		debug(" >> freeing resource: %s", pair.first.c_str());
		if(pair.second) {
			pair.second->free();
			delete pair.second;
		}
	}
	debug("all resources freed");
	ResourceManager::_textures.clear();
}
