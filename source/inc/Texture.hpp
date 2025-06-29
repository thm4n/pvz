#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>
#include <exception>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

#include "Logger.hpp"
#include "ResourceType.hpp"

class Texture {
public:
    // Initializes variables
    Texture();

    // Deallocates memory
    ~Texture();

    // Loads image at specified path
    void loadImageFromFile(SDL_Renderer *renderer, std::string path);
    void loadTextFromFont(SDL_Renderer *renderer, std::string text, TTF_Font* ttf, SDL_Color color);
    void loadAudioFromFile(SDL_Renderer *renderer, std::string path);

    // Deallocates texture
    void free();

    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(Uint8 alpha);

    // Renders texture at given point
    void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = nullptr);

    // Gets image dimensions
    int getWidth() const;
    int getHeight() const;

private:
    // The actual hardware texture
	fs::path _content;
    SDL_Texture *_texture;
	ResourceType _type;

    // Image dimensions
    int _width;
    int _height;
};
