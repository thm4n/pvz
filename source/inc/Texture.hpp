#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "Logger.hpp"

class Texture {
public:
    //Initializes variables
    Texture();

    //Deallocates memory
    ~Texture();

    //Loads image at specified path
    void loadFromFile(SDL_Renderer* renderer, std::string path);

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //Set blending
    void setBlendMode(SDL_BlendMode blending);

    //Set alpha modulation
    void setAlpha(Uint8 alpha);
    
    //Renders texture at given point
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr);

    //Gets image dimensions
    int getWidth() const;
    int getHeight() const;

private:
    //The actual hardware texture
    SDL_Texture* _texture;

    //Image dimensions
    int _width;
    int _height;
};
