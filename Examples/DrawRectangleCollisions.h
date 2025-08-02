//
// Created by judelhuu on 7/6/25.
//

#ifndef DRAWRECTANGLECOLLISIONS_H
#define DRAWRECTANGLECOLLISIONS_H

#include "../Classes/include/Sprite.h"

void DrawRectangleCollions() {
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("failed to initialized sdl %s\n", SDL_GetError());
        return;
    }

    // Window
    SDL_Window* win = SDL_CreateWindow("Hello!, World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    // Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    // Surface

    Sprite rect1(renderer, "/home/judelhuu/CLionProjects/SDL_Tutorial/Images/MangaGirl1.bmp");
    Sprite rect2(renderer, "/home/judelhuu/CLionProjects/SDL_Tutorial/Images/MangaGirl2.bmp");

    rect1.SetRectangleProperties(0,0,200,200);
    rect2.SetRectangleProperties(200,200,200,200);



    // Game Loop
    bool isRunning = true;
    while (isRunning)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        if (event.button.button == SDL_BUTTON_LEFT) {

        }

        if (rect1.IsColliding(rect2)) {
            std::cout << "'Kiss noises*" << std::endl;
        }

        // Set Background color Black
        SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Set Drawing Color White
        SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);


        // Draw TextureRect
        rect1.SetRectangleProperties(640/2-75,480/2-75,150,150);
        rect2.SetRectangleProperties(mouseX-75, mouseY-75, 150,150);
        // Render TextureRect
        rect1.Render(renderer);
        rect2.Render(renderer);

        SDL_RenderPresent(renderer);
    }


    SDL_DestroyWindow(win);
    SDL_Quit();
}

#endif //DRAWRECTANGLECOLLISIONS_H
