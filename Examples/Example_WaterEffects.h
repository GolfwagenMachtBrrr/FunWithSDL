//
// Created by judelhuu on 7/4/25.
//

#ifndef EXAMPLE_WATEREFFECTS_H
#define EXAMPLE_WATEREFFECTS_H

#include <SDL2/SDL.h>

void Example_DrawWaterEffect()
{
    //Init
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    // Window
    SDL_Window* win = SDL_CreateWindow("Hello!, World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    // Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    // Surface
    SDL_Surface* surface = SDL_LoadBMP("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/pool2.bmp");
    // Textures, we copy the texture and move the copies torwards each other.
    SDL_Texture* texture  = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface);
    // Texture holds Surface, so we can delete it
    SDL_FreeSurface(surface);

    // Rectangles
    auto* rect = new SDL_Rect;
    rect->x = 0;
    rect->y = 0;
    rect->w = 640;
    rect->h = 480;

    auto* rect2 = new SDL_Rect;
    rect2->x = -639;
    rect2->y = 0;
    rect2->w = 640;
    rect2->h = 480;

    auto* rect3 = new SDL_Rect;
    rect3->x = 0;
    rect3->y = 0;
    rect3->w = 640;
    rect3->h = 480;

    auto* rect4 = new SDL_Rect;
    rect4->x = 0;
    rect4->y = -480;
    rect4->w = 640;
    rect4->h = 480;


    // Game Loop
    bool isRunning = true;
    while (isRunning)
    {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_ADD);
                }
                else if (event.button.button == SDL_BUTTON_MIDDLE) {
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_BLEND);
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_MOD);
                }
            }
        }


        // Set Background color Black
        SDL_SetRenderDrawColor(renderer, 0,0,0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        int w,h;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        SDL_Delay(20);

        // Moving the textures rigth
        rect->x++; if (rect->x > 639) {rect->x = -639; }
        rect2->x++; if (rect2->x > 639) {rect2->x = -639; }
        // Moving the textures down
        rect3->y++; if ( rect3->y > 479) { rect3->y = -480; }
        rect4->y++; if ( rect4->y > 479) { rect4->y = -480; }
        ;
        // Draw TextureRect
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
        SDL_RenderCopy(renderer, texture, nullptr, rect);
        SDL_RenderCopy(renderer, texture, nullptr, rect2);

        SDL_RenderCopy(renderer, texture2, nullptr, rect3);
        SDL_RenderCopy(renderer, texture2, nullptr, rect4);

        SDL_RenderPresent(renderer);
    }

    delete rect;
    delete rect2;
    delete rect3;
    delete rect4;

    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

#endif //EXAMPLE_WATEREFFECTS_H
