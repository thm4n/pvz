#pragma once
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Logger.hpp"
#include "ResourceManager.hpp"
#include "Texture.hpp"

class Graphics {
public:
	Graphics();
	~Graphics();

	void initSDL();
	void initGraphics();

	void frameStart();
	void frameEnd();

	void setTargetFPS(int targetFPS);
	int getTargetFPS() const;
	int getFrameDuration() const;

private:
	friend class ResourceManager;
	friend class Texture;

	int _targetFPS;
	double _frameDuration;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	// tick counters
	struct tickCounters {
		Uint64 now;
		Uint64 last;
		double deltaTime;
	} _tickCounters;
};
