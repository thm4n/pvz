#include "inc/Font.hpp"

Font::Font(const std::string& fontPath, uint fontSize) {
	this->_path = fs::path(fontPath);
	if(!fs::exists(this->_path)) {
		error("Font file %s does not exist.", this->_path.string().c_str());
		throw std::runtime_error("Font file does not exist.");
	}
	this->_size = fontSize;
	this->_font = nullptr;
}

Font::~Font() {
	free();
}

void Font::loadFontFile() {
	if(this->_font) {
		error("Font already loaded.");
		throw std::runtime_error("Font already loaded.");
	}

	this->_font = TTF_OpenFont(this->_path.string().c_str(), this->_size);
	if(!this->_font) {
		error("Failed to load font from %s: %s", this->_path.string().c_str(), TTF_GetError());
		throw std::runtime_error("Failed to load font");
	}
	debug("Font loaded from %s with size %d", this->_path.string().c_str(), this->_size);
}

void Font::free() {
	if(this->_font) {
		TTF_CloseFont(this->_font);
		this->_font = nullptr;
		this->_size = 0;
	}
}

uint Font::getSize() const {
	return this->_size;
}

const fs::path& Font::getPath() const {
	return this->_path;
}

TTF_Font* Font::getFont() const {
	return this->_font;
}
