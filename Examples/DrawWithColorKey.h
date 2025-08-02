//
// Created by judelhuu on 7/4/25.
// Blendtastic
//

#ifndef BLENDINGWITHBLENDER_H
#define BLENDINGWITHBLENDER_H

#include <SDL2/SDL.h>

void DrawTransparent_2()
{
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("failed to initialized sdl %s\n", SDL_GetError());
        return;
    }

    // Window
    SDL_Window* win = SDL_CreateWindow("Hello!, World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    // Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    // Surface
    SDL_Surface* surface = SDL_LoadBMP("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/kong.bmp");
    // Set color Key
    SDL_SetColorKey(surface,SDL_TRUE, SDL_MapRGB(surface->format,0xFF, 0, 0xFF));

    // Texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Texture holds Surface, so we can delete it

    // Rechtagle to Draw
    SDL_Rect* rect;
    rect->x = 320-64; // Position x/y
    rect->y = 240-64;
    rect->w = 64; // Width/Height
    rect->h = 64;

    // Game Loop
    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        if (event.button.button == SDL_BUTTON_LEFT) {

        }
        // Set Background color Black
        SDL_SetRenderDrawColor(renderer, 0,0,0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Set Drawing Color White
        SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);

        // Draw Line
        SDL_RenderDrawLine(renderer, 0,0,640,480);

        // Draw TextureRect
        SDL_RenderCopy(renderer, texture, nullptr, rect);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

#endif //BLENDINGWITHBLENDER_H
