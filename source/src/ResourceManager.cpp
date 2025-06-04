#include "inc/ResourceManager.hpp"

ResourceManager::ResourceManager(Graphics* graphics) {
	debug("setting ResourceManager");
	this->_graphics = graphics;

	debug("setting Texture::_graphics");
	Texture::setGraphics(this->_graphics);
}

ResourceManager::~ResourceManager() {
	info("freeing all resources");
	Texture* currentTexture = nullptr;
	for(auto it = this->_textures.begin(); it != this->_textures.end(); it++) {
		currentTexture = (*it);
		if(currentTexture) {
			debug("freeing resource: %s", currentTexture->getName().c_str());
			currentTexture->free();
			delete currentTexture;
		}
	}
	this->_textures.clear();
}

// currently name = path
// future: map<name, path>
void ResourceManager::loadResource(std::string name) {
	Texture* texture = nullptr;

	if(name.empty()) {
		error("Cannot create texture from name: %s", name.c_str());
		return;
	}

	debug("initializing texture: %s", name.c_str());
	texture = new Texture(name);
	if(!texture) {
		error("Failed to initialized texture class for %s", name.c_str());
		return;
	}

	this->_textures.push_back(texture);
}

void ResourceManager::freeResource(Texture* resource) {
	if(resource) {
		debug("freeing resource: %s", resource->getName().c_str());
		resource->free();
		auto it = std::find(this->_textures.begin(), this->_textures.end(), resource);
		if(it != this->_textures.end()) {
			this->_textures.erase(it);
		}
		else {
			error("untracked resource freed: %s", resource->getName().c_str());
		}

		delete resource;
	}
	warn("cant free not initialized resource");
}
