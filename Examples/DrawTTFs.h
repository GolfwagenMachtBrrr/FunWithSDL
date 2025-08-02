//
// Created by judelhuu on 7/5/25.
//

#ifndef DRAWTTFS_H
#define DRAWTTFS_H

#include <SDL2/SDL_ttf.h>

void DrawFont()
{
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("failed to initialized sdl %s\n", SDL_GetError());
        return;
    }

    // Window
    SDL_Window* win = SDL_CreateWindow("Hello!, World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    // Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // TTF Initialization
    TTF_Init();

    // Font
    TTF_Font* font = TTF_OpenFont("/home/judelhuu/CLionProjects/SDL_Tutorial/Fonts/ExampleFont.ttf", 32);

    // Text2Surface
    SDL_Surface* surfaceText = TTF_RenderText_Solid(font, "Hello my Friend", {255,255,255});

    // Texture
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);

    // Free surface memory
    SDL_FreeSurface(surfaceText);



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
            }
        }


        // Set Background color Black
        SDL_SetRenderDrawColor(renderer, 0,0,0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Set Drawing Color White
        SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);

        // Draw TextureRect
        SDL_RenderCopy(renderer, textureText, nullptr, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textureText);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

#endif //DRAWTTFS_H
