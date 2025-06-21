#include "inc/Texture.hpp"

Texture::Texture() {
	this->_texture = nullptr;
	this->_width = 0;
	this->_height = 0;
}

Texture::~Texture() {
	free();
}

void Texture::loadFromFile(SDL_Renderer* renderer, std::string path) {
	if(this->_texture != nullptr) {
        this->free();
    }

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(!loadedSurface) {
		error("Unable to load image %s! SDL_image Error: %s", path.c_str(), IMG_GetError());
		// throw std::runtime_error("Unable to load image");
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        this->_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(!this->_texture) {
			error("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			// throw std::runtime_error("Unable to create texture");
		}
		else {
			//Get image dimensions
			this->_width = loadedSurface->w;
			this->_height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
}

void Texture::free() {
	if(this->_texture) {
		SDL_DestroyTexture(this->_texture);
		this->_texture = nullptr;
		this->_width = 0;
		this->_height = 0;
	}
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	//Modulate texture rgb
	SDL_SetTextureColorMod(this->_texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
	//Set blending function
	SDL_SetTextureBlendMode(this->_texture, blending);
}
		
void Texture::setAlpha(Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(this->_texture, alpha);
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, this->_width, this->_height };

	//Set clip rendering dimensions
	if(clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(renderer, this->_texture, clip, &renderQuad);
}

int Texture::getWidth() const {
	return this->_width;
}

int Texture::getHeight() const {
	return this->_height;
}
