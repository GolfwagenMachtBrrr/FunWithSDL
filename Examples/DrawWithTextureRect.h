//
// Created by judelhuu on 7/4/25.
//

#ifndef DRAWWITHTEXTURERECT_H
#define DRAWWITHTEXTURERECT_H

#include <SDL2/SDL.h>
#include "../Classes/include/Sprite.h"

void DrawTexture()
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
    SDL_Surface* surface = SDL_LoadBMP("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/MangaGirl1.bmp");
    // Texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Texture holds Surface, so we can delete it

    // Rechtagle to Draw
    SDL_Rect* rect;
    rect->x = 0; // Position x/y
    rect->y = 0;
    rect->w = 640; // Width/Height
    rect->h = 480;

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
        SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Set Drawing Color White
        SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);

        // Draw TextureRect
        SDL_RenderCopy(renderer, texture, nullptr, rect);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

#endif //DRAWWITHTEXTURERECT_H
