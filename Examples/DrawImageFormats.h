//
// Created by judelhuu on 7/6/25.
//

#ifndef DRAWIMAGEFORMATS_H
#define DRAWIMAGEFORMATS_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "png.h"

void DrawImageFormat() {

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("failed to initialized sdl %s\n", SDL_GetError());
        return;
    }


    // Window
    SDL_Window* win = SDL_CreateWindow("Hello!, World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    // Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


    // Inti format
    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if ( (initStatus & flags) != flags) {std::cout << "IMG_Init Failed: " << IMG_GetError() << std::endl;} // Test for diff between initialized format

    //Surface - Well bmp it is:
    SDL_Surface* surface = IMG_Load("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/MangaGirl2.png");
    if (!surface) {std::cout << "IMG_Load Failed: " << IMG_GetError() << std::endl; }

    // Texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Free surface memory
    SDL_FreeSurface(surface);

    SDL_Rect rect;
    rect.x = 10;
    rect.y = 10;
    rect.w = 400;
    rect.h = 100;


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

        SDL_RenderCopy(renderer, texture, NULL, &rect);

        SDL_RenderPresent(renderer);

    }


    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

#endif //DRAWIMAGEFORMATS_H
