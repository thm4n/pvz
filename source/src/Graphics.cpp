#include "inc/Graphics.hpp"

Graphics::Graphics() {
    this->_targetFPS = 60;
    this->_frameDuration = 1000.0 / (double)this->_targetFPS;

    this->_window = nullptr;
    this->_renderer = nullptr;
}

Graphics::~Graphics() {
    if(this->_renderer) {
        SDL_DestroyRenderer(this->_renderer);
        debug("succesfully destroyed Graphics::_renderer");
    }

    if(this->_window) {
        SDL_DestroyWindow(this->_window);
        debug("succesfully destroyed Graphics::_window");
    }

    debug("terminating SDL Modules");
    Mix_CloseAudio();
    debug(" > SDL Mixer Module - terminated succesfully");
    TTF_Quit();
    debug(" > SDL TTF Module - terminated succesfully");
    IMG_Quit();
    debug(" > SDL Image Module - terminated succesfully");
    SDL_Quit();
    debug(" > SDL2 - terminated succesfully");
}

void Graphics::initSDL() {
    int status = 0;

    status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if(status < 0) {
        fatal("SDL Init error %s", SDL_GetError());
        // throw exception here
    }

    int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    status = IMG_Init(img_flags);
    if(status & img_flags) {
        debug("SDL Image module initialized succesfully with flags: PNG, JPG");
    }
    else {
        error("SDL Image module failed to initialize properly: %s", IMG_GetError());
        // throw exception here
    }

    status = TTF_Init();
    if(status == -1) {
        error("SDL TTF module failed to initialize properly: %s", TTF_GetError());
        // throw exception here
    }
    else {
        debug("SDL TTF module initialized succesfully");
    }

    status = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if(status < 0) {
        error("SDL Mixer module failed to initialize properly: %s", Mix_GetError());
        // throw exception here
    }
    else {
        debug("SDL Mixer module initialized succesfully");
    }
}

void Graphics::initGraphics() {
    this->_window = SDL_CreateWindow(
        "Plants Vs. Zombies",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        0, 0, 
        SDL_WINDOW_FULLSCREEN_DESKTOP // consider removing _DESKTOP (_DESKTOP is for borderless)
    );
    if(this->_window)
        debug("SDL_Window initialized succesfully");
    else
        error("SDL_CreateWinow failed: %s", SDL_GetError());

    this->_renderer = SDL_CreateRenderer(
        this->_window,
        -1,
        SDL_RENDERER_ACCELERATED 
    );
    if(this->_renderer)
        debug("SDL_Renderer initialized succesfully");
    else
        error("SDL_CreateRenderer failed: %s", SDL_GetError());
}

void Graphics::frameStart() {
    this->_tickCounters.last = this->_tickCounters.now;
    this->_tickCounters.now = SDL_GetPerformanceCounter();
    this->_tickCounters.deltaTime = (double)((this->_tickCounters.now - this->_tickCounters.last) * 1000.f) / SDL_GetPerformanceFrequency();
}

void Graphics::frameEnd() {
    double frameTime = (double)((SDL_GetPerformanceCounter() - this->_tickCounters.now) * 1000.f) / SDL_GetPerformanceFrequency();
    double delayTime = this->_frameDuration - frameTime;

    if (delayTime > 0) {
        SDL_Delay((Uint32)delayTime);
    }
}

void Graphics::setTargetFPS(int targetFPS) {
    this->_targetFPS = targetFPS;
    this->_frameDuration = 1000.0 / (double)targetFPS;
}

int Graphics::getTargetFPS() const {
    return this->_targetFPS;
}

int Graphics::getFrameDuration() const {
    return this->_frameDuration;
}
