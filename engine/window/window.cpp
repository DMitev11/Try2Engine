#include "./window.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h> 
// LazyFooTutorial
bool Window::init()
{
    // Initialization flag
    bool success = true; 

    // Create window
    SDL_Window *gWindow = SDL_CreateWindow("SDL Tutorial", 1000, 1000, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create renderer for window
        SDL_Renderer *gRenderer = SDL_CreateRenderer(gWindow, NULL, SDL_RENDERER_ACCELERATED);
        if (gRenderer == NULL)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

            // Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
        }
    } 
    return success;
}