//Using SDL and standard IO
#include <SDL.h>
#include <memory>
#include <iostream>
#include <stdlib.h>

//Screen dimension constants
constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    {
        std::shared_ptr<SDL_Window> window(
            SDL_CreateWindow("SDL Tutorial",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
            ), // Custom Constructor
            [](SDL_Window* ptr) {
                std::cerr << "Deleted: Window" << std::endl;
                SDL_DestroyWindow(ptr);
            }
             //Custom Deleter
        );

        if (window.get() == nullptr) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return EXIT_FAILURE;
        }

        std::shared_ptr<SDL_Renderer> renderer(
            SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), 
            [](SDL_Renderer* rend) {
                std::cerr << "Deleted: Renderer" << std::endl;
                SDL_DestroyRenderer(rend);
            }
        );

        SDL_Event e;
        bool quit = false;

        while (quit == false) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            SDL_SetRenderDrawColor(renderer.get(), 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(renderer.get());

            SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
            SDL_SetRenderDrawColor(renderer.get(), 0x00, 0xFF, 0x00, 0xFF);
            SDL_RenderDrawRect(renderer.get(), &outlineRect);

            SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0x00, 0xFF);
            for (int i = 0; i < SCREEN_HEIGHT; i += 4)
            {
                SDL_RenderDrawPoint(renderer.get(), SCREEN_WIDTH / 2, i);
            }

            SDL_RenderPresent(renderer.get());
            
        }
    }
    

    SDL_Quit();
    return EXIT_SUCCESS;
}