//Using SDL and standard IO
#include <SDL.h>
#include <memory>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    SDL_Surface* screenSurface = nullptr;

    int result = SDL_Init(SDL_INIT_VIDEO);

    if (result < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    std::shared_ptr<SDL_Window> window(
        SDL_CreateWindow("SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        ), // Custom Constructor
        SDL_DestroyWindow //Custom Deleter
    );

    if (window.get() == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }


    screenSurface = SDL_GetWindowSurface(window.get());

    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    SDL_UpdateWindowSurface(window.get());

    SDL_Event e;
    bool quit = false;

    while (quit == false) { 
        while (SDL_PollEvent(&e)) { 
            if (e.type == SDL_QUIT) { 
                quit = true; 
            }
        } 
    }

    //Quit SDL subsystems
    SDL_Quit();

    return EXIT_SUCCESS;
}