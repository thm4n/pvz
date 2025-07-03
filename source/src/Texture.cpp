#include "inc/Texture.hpp"

Texture::Texture() {
    this->_texture = nullptr;
    this->_width = 0;
    this->_height = 0;
	this->_type = ResourceType::Uninitialized;
}

Texture::~Texture() { free(); }

void Texture::loadImageFromFile(SDL_Renderer* renderer, std::string path) {
    if (this->_texture) {
        this->free();
    }

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        error("Unable to load image %s! SDL_image Error: %s", path.c_str(),
              IMG_GetError());
        throw std::runtime_error("Unable to load image");
    }
	SDL_SetColorKey(loadedSurface, SDL_TRUE,
					SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	this->_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (!this->_texture) {
		error("Unable to create texture from %s! SDL Error: %s\n",
				path.c_str(), SDL_GetError());
		throw std::runtime_error("Unable to create texture");
	}
	// Get image dimensions
	this->_width = loadedSurface->w;
	this->_height = loadedSurface->h;
	debug("%s created with dimensions: %d x %d", path.c_str(), this->_width, this->_height);


	SDL_FreeSurface(loadedSurface);
	this->_content = path;
	this->_type = ResourceType::IMAGE;
}

void Texture::loadTextFromFont(SDL_Renderer *renderer, std::string text, TTF_Font* ttf, SDL_Color color) {
	if (this->_texture != nullptr) {
		this->free();
	}
	
	SDL_Surface* textSurface = TTF_RenderText_Solid(ttf, text.c_str(), color);
	if (!textSurface) {
		error("Unable to render text surface! SDL_ttf Error: %s", TTF_GetError());
		throw std::runtime_error("Unable to render text surface");
	}
	this->_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!this->_texture) {
		error("Unable to create texture from rendered text! SDL Error: %s", SDL_GetError());
		throw std::runtime_error("Unable to create texture from rendered text");
	}

	this->_width = textSurface->w;
	this->_height = textSurface->h;

	SDL_FreeSurface(textSurface);
	this->_content = text;
	this->_type = ResourceType::FONT;
}

void Texture::loadAudioFromFile(SDL_Renderer *renderer, std::string path) {
	warn("WIP");
	this->_content = path;
	this->_type = ResourceType::SOUND;
}

void Texture::free() {
    if (this->_texture) {
        SDL_DestroyTexture(this->_texture);
        this->_texture = nullptr;
        this->_width = 0;
        this->_height = 0;
    }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    // Modulate texture rgb
    SDL_SetTextureColorMod(this->_texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
    // Set blending function
    SDL_SetTextureBlendMode(this->_texture, blending);
}

void Texture::setAlpha(Uint8 alpha) {
    // Modulate texture alpha
    SDL_SetTextureAlphaMod(this->_texture, alpha);
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, this->_width, this->_height};

    // Set clip rendering dimensions
    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopy(renderer, this->_texture, clip, &renderQuad);
}

SDL_Texture* Texture::getTexture() const {
	return this->_texture;
}

int Texture::getWidth() const { return this->_width; }

int Texture::getHeight() const { return this->_height; }
