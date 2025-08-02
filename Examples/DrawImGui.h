//
// Created by judelhuu on 8/2/25.
//

#ifndef DRAWIMGUI_H
#define DRAWIMGUI_H

#include <SDL2/SDL.h>
#include <imgui.h>

void DrawIMGUI()
{
    SDL_Window* window=nullptr;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("C++ SDL2 Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 20*16,15*16,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


    SDL_Surface* tile_map_surface = SDL_LoadBMP("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Tiles/tiles.bmp");
    SDL_Texture* tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);
    SDL_FreeSurface(tile_map_surface);


    // retr pointer to keys
    const Uint8* keys = SDL_GetKeyboardState(NULL);

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

        // Set Background color Black
        SDL_SetRenderDrawColor(renderer, 0x66,0,0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);


        // Draw TextureRect
        SDL_RenderPresent(renderer);
    }


}

#endif //DRAWIMGUI_H
