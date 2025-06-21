#include "SDL2/SDL.h"
#include "SDL_image.h"

#include "inc/ResourceManager.hpp"
#include "inc/Texture.hpp"
#include "inc/Logger.hpp"

bool init();
bool loadMedia();
void close();

int main();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

std::vector<std::string> gResourcePaths = {
    "resources/Diamond.png",
    "resources/Diamond_shine1.png",
    "resources/Diamond_shine2.png",
    "resources/Diamond_shine3.png",
    "resources/Diamond_shine4.png",
    "resources/Diamond_shine5.png"
};
int gframes = gResourcePaths.size();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init() {
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		error("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			warning("Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(!gWindow) {
			error("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(!gRenderer) {
				error("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					error("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void close() {
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main() {
    if(!init()) {
        error("Failed to initialize!");
        return 1;
    }

    ResourceManager* resourceManager = new ResourceManager(gRenderer);
    Texture* currTexture = nullptr;

    for(const auto& resourcePath : gResourcePaths) {
        ResourceManager::loadResource(resourcePath);
    }

    bool quit = false;

    //Event handler
    SDL_Event e;

    //Current animation frame
    int frame = 0;

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        //Render current frame
        if(gframes) {
            currTexture = ResourceManager::getResource(gResourcePaths[frame % gframes]);
            currTexture->render( gRenderer, (SCREEN_WIDTH - currTexture->getWidth()) / 2, (SCREEN_HEIGHT - currTexture->getHeight()) / 2);
        }
        //Update screen
        SDL_RenderPresent( gRenderer );

        //Go to next frame
        ++frame;
        if(frame == gframes)
            frame = 0;

        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    }

    delete(resourceManager);
    close();

    return 0;
}
