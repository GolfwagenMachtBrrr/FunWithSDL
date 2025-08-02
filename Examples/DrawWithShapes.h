//
// Created by judelhuu on 7/4/25.
//

#ifndef DRAWWITHSHAPES_H
#define DRAWWITHSHAPES_H

#include <SDL2/SDL.h>
#include <glad/glad.h>

void DrawShape()
{
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("failed to initialized sdl %s\n", SDL_GetError());
        return;
    }

    // Window
    SDL_Window* win = SDL_CreateWindow("Hello!, World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    // Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // Rechtagle to Draw
    SDL_Rect* rect;
    rect->x = 0; // Position x/y
    rect->y = 0;
    rect->w = 32; // Width/Height
    rect->h = 32;

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


        // Draw Line
        SDL_RenderDrawLine(renderer, 5,5,100,120); // Drawing
        // Draw Rectangle
        SDL_RenderDrawRect(renderer, rect);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
}


#endif //DRAWWITHSHAPES_H
