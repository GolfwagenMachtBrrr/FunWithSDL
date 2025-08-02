//
// Created by judelhuu on 7/6/25.
//

#ifndef EXAMPLE_TEXTUREDRECTANGLES_H
#define EXAMPLE_TEXTUREDRECTANGLES_H

#include "../Classes/include/Sprite.h"

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <memory>


void Example_DrawTexturedRect()
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

    std::vector<std::shared_ptr<Sprite>> rectangles;
    for (int i = 0; i < 200; i++) {
        std::shared_ptr<Sprite> rect =
            std::make_shared<Sprite>(renderer, "/home/judelhuu/CLionProjects/SDL_Tutorial/Images/MangaGirl1.bmp");
        rectangles.push_back(rect);
    }

    for (int i = 0; i < rectangles.size(); i++) {
        rectangles[i]->SetRectangleProperties(i, i,200,200);
    }


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
        for (auto& rect : rectangles) {
            rect->Render(renderer);
        }


        SDL_RenderPresent(renderer);
    }


    SDL_DestroyWindow(win);
    SDL_Quit();
}

#endif //EXAMPLE_TEXTUREDRECTANGLES_H
