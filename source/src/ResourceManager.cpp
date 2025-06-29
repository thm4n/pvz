#include "inc/ResourceManager.hpp"

SDL_Renderer* ResourceManager::_renderer = nullptr;
std::map<const std::string, Texture*> ResourceManager::_textures =
	std::map<const std::string, Texture*>();
std::map<const std::string, Font*> ResourceManager::_fonts =
	std::map<const std::string, Font*>();

ResourceManager::ResourceManager(SDL_Renderer* renderer) {
    if (ResourceManager::_renderer || !ResourceManager::_textures.empty()) {
        error("ResourceManager already initialized");
        throw std::runtime_error("ResourceManager already initialized");
    }
    if (!renderer) {
        error("Renderer cannot be null");
        throw std::runtime_error("Renderer cannot be null");
    }
    ResourceManager::_renderer = renderer;
}

ResourceManager::~ResourceManager() {
    ResourceManager::_renderer = nullptr;
    ResourceManager::freeAll();
}

void ResourceManager::loadImageResource(const std::string& resourceName, const std::string& resourcePath) {
	Texture* texture = new Texture();
    texture->loadImageFromFile(ResourceManager::_renderer, resourcePath);
    ResourceManager::_textures.insert({resourceName, texture});
    debug("%s - Image resource loaded as '%s'", resourcePath.c_str(), resourceName.c_str());
}

void ResourceManager::loadTextTexture(const std::string& name, const std::string& text, const std::string& font, uint size, SDL_Color color) {
	if(text.empty()) {
		error("Text cannot be empty");
		throw std::runtime_error("Text cannot be empty");
	}

	Font* ttf = ResourceManager::getFont(font, size);
	if (!ttf) {
		error("Font '%s' with size %u not found", font.c_str(), size);
		throw std::runtime_error("Font not found");
	}

	Texture* texture = new Texture();
	texture->loadTextFromFont(ResourceManager::_renderer, text, ttf->getFont(), color);
	ResourceManager::_textures.insert({name, texture});
}

void ResourceManager::loadAudioResource(const std::string& resourceName, const std::string& resourcePath) {
	warn("WIP");
    debug("%s - Audio resource loaded as '%s'", resourcePath.c_str(), resourceName.c_str());
}

void ResourceManager::loadFontResource(const std::string& resourceName, const std::string& resourcePath, uint size) {
	Font* font = nullptr;
	std::string resName = resourceName + ":" + std::to_string(size);

	font = new Font(resourcePath, size);
	if (!font) {
		error("Failed to create font object for %s", resourcePath.c_str());
		throw std::runtime_error("Failed to create font object");
	}
	font->loadFontFile();
	ResourceManager::_fonts.insert({resName, font});
    debug("%s - Font resource loaded as '%s'", resourcePath.c_str(), resName.c_str());
}

Texture* ResourceManager::getResource(const std::string& resourcePath) {
	debug("Searching for resource: %s", resourcePath.c_str());
    auto it = ResourceManager::_textures.find(resourcePath);
    if (it != ResourceManager::_textures.end()) 
		return it->second;
    return nullptr;
}

Font* ResourceManager::getFont(const std::string& resourceName, uint size) {
	std::string resName = resourceName + ":" + std::to_string(size);
	debug("Searching for font: %s", resName.c_str());
	auto it = ResourceManager::_fonts.find(resourceName);
	if (it != ResourceManager::_fonts.end() && it->second)
		return it->second;
	return nullptr;
}

void ResourceManager::freeAll() {
    info("freeing all resources:");

	debug("freeing all textures");
    for (auto it = ResourceManager::_textures.begin(); it != ResourceManager::_textures.end(); ++it) {
        debug(" >> freeing resource: %s", it->first.c_str());
        if (it->second) {
            delete it->second;
        }
		it->second = nullptr;
    }

	debug("freeing all fonts");
	for (auto it = ResourceManager::_fonts.begin(); it != ResourceManager::_fonts.end(); ++it) {
		debug(" >> freeing font: %s", it->first.c_str());
		if (it->second) {
			delete it->second;
			it->second = nullptr;
		}
	}

    ResourceManager::_textures.clear();
	ResourceManager::_fonts.clear();
	ResourceManager::_renderer = nullptr;
	debug("ResourceManager cleared");
}
