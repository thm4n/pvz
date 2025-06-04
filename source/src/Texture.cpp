#include "inc/Texture.hpp"

Graphics* Texture::_graphics = nullptr;

Texture::Texture(const std::string& path) {
	debug("setting Texture");

	this->_texture = nullptr;
	this->_width = 0;
	this->_height = 0;
	this->_filePath = path;
	
	if(!this->_graphics) {
		error("Cannot create Texture without initialized Graphics");
	}
	else {
		debug("Texture::_graphics already set");
	}

	if(!path.empty()) {
		this->loadFromFile();
	}
}

Texture::~Texture() {
	this->free();
}

void Texture::setGraphics(Graphics* graphics) {
	if (!Texture::_graphics)
		Texture::_graphics = graphics;
}

void Texture::loadFromFile(const std::string& path) {
	if(this->_filePath == "" && path == "") {
		error("no resource filepath given to load");
		return;
	}
	this->_filePath = path;
	debug("loading %s from file", this->_filePath);

	debug("checking if Texture<%s>::_texture is nullptr", this->_filePath);
	if(this->_texture) {
		error("Texture::loadFromFile attempted on a non-empty Texture class");
		return;
	}

	debug("loading image from %s", this->_filePath.c_str());
	SDL_Surface* loadedSurface = IMG_Load(this->_filePath.c_str());
	if(!loadedSurface) {
		error("Unable to load image %s!\n >> SDL_Image Error: %s", this->_filePath.c_str(), IMG_GetError());
		return;
	}

	debug("setting color key for SDL_Surface");
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xff, 0xff));

	debug("creating texture from surface");
	this->_texture = SDL_CreateTextureFromSurface(this->_graphics->_renderer, loadedSurface);
	if(this->_texture) {
		debug("Texture successfully created!");
		info("Created Texture Details:\n >> name: %s\n >> width, height: (%d, %d)", this->_filePath.c_str(), this->_width, this->_height);
		this->_width = loadedSurface->w;
		this->_height = loadedSurface->h;
	}
	else {
		error("could not create texture from surface for %s!\n >> SDL Error: %s", this->_filePath.c_str(), SDL_GetError());
	}

	debug("surface freed");
	SDL_FreeSurface(loadedSurface);
}

void Texture::free() {
	debug("Freeing texture %s", this->_filePath.c_str());
	if(this->_texture) {
		SDL_DestroyTexture(this->_texture);
		this->_width = 0;
		this->_height = 0;
		this->_filePath.clear();
	}
}

void Texture::render(int x, int y) {
	debug("Rendering %s at (%d,%d)", this->_filePath.c_str(), x, y);
	SDL_Rect renderQuad = {x, y, this->_width, this->_height};
	SDL_RenderCopy(this->_graphics->_renderer, this->_texture, nullptr, &renderQuad);
}

int Texture::getWidth() const {
	return this->_width;
}

int Texture::getHeight() const {
	return this->_height;
}

const std::string& Texture::getName() const {
	return this->_filePath;
}
