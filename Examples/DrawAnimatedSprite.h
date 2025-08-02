//
// Created by judelhuu on 7/6/25.
//

#ifndef DRAWANIMATEDSPRITE_H
#define DRAWANIMATEDSPRITE_H

#include "../Classes/include/AnimatedSprite.h"
#include "../Classes/include/Sprite.h"

#include <SDL2/SDL.h>
#include <memory>

void DrawAnimatedSprite() {
    SDL_Window* window=nullptr;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }

    window = SDL_CreateWindow("C++ SDL2 Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


    AnimatedSprite animatedSprite(renderer,"/home/judelhuu/CLionProjects/SDL_Tutorial/Images/edited.bmp");
    animatedSprite.Draw(200,200,150,150);


    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
        }
        // (2) Handle Updates

        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Do our drawing
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);

        static int frameNumber = 0;

        animatedSprite.PlayFrame(0,0,170,110,frameNumber);
        animatedSprite.Render(renderer);
        frameNumber++;
        if(frameNumber>6){
            frameNumber= 0;
        }

        // Finally show what we've drawn
        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);

    // our program.
    SDL_Quit();
}



#endif //DRAWANIMATEDSPRITE_H
