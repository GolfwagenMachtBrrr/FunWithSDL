//
// Created by judelhuu on 7/3/25.
//

#ifndef EDITINGSDL_SURFACE_H
#define EDITINGSDL_SURFACE_H
#include <SDL2/SDL.h>
#include <glad/glad.h>


void SetPixel(SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    SDL_LockSurface(surface);
    std::cout << "Button left " << x << "," << y << std::endl;

    Uint8 bpp = surface->format->BytesPerPixel; // bpp? xD

    Uint8* pixelArray = (Uint8*)surface->pixels;
    pixelArray[y*surface->pitch + x*bpp+0] = g; // API says RGB is GBR
    pixelArray[y*surface->pitch + x*bpp+1] = b;
    pixelArray[y*surface->pitch + x*bpp+2] = r;

    SDL_UnlockSurface(surface);
}

void EditSDLSurface() {

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("failed to initialized sdl %s\n", SDL_GetError());
        return;
    }

    // Window
    SDL_Window* win = SDL_CreateWindow("Hello!, World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    // Surface for loading graphical "data"
    SDL_Surface* screen = SDL_GetWindowSurface(win);

    // Game Loop
    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        int x,y;
        Uint32 buttons = SDL_GetMouseState(&x,&y);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.button.button == SDL_BUTTON_LEFT) {
                SetPixel(screen,x,y, 0,0,255);
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                SetPixel(screen,x,y, 255,0,0);
            }
        }

        SDL_UpdateWindowSurface(win);
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
}

#endif //EDITINGSDL_SURFACE_H
