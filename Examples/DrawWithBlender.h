//
// Created by judelhuu on 7/4/25.
//

#ifndef TRANSPARENTPIXELS_H
#define TRANSPARENTPIXELS_H

#include <SDL2/SDL.h>

struct MyRect {
    int x, y, w, h;
};

void DrawBlended()
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


    auto* rect2 = new SDL_Rect;
    rect2->x = 320-64; // Position x/y
    rect2->y = 240-64;
    rect2->w = 64*2; // Width/Height
    rect2->h = 64*2;


    auto* rect = new SDL_Rect;
    rect->x = 320-64; // Position x/y
    rect->y = 240-64;
    rect->w = 64*2; // Width/Height
    rect->h = 64*2;

    // Game Loop
    bool isRunning = true;
    while (isRunning)
    {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_MOUSEMOTION) {
                rect2->x = event.motion.x - 64;
                rect2->y = event.motion.y - 64;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);
                }
                if (event.button.button == SDL_BUTTON_MIDDLE) {
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);
                }
            } else {
                SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
            }
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
        SDL_RenderCopy(renderer, texture, nullptr, rect2);

        SDL_RenderPresent(renderer);
    }

    delete rect;
    delete rect2;

    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

#endif //TRANSPARENTPIXELS_H
