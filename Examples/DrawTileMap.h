//1
// Created by judelhuu on 8/1/25.
//

#ifndef DRAWTILEMAP_H
#define DRAWTILEMAP_H
#include <SDL2/SDL.h>
#include <iostream>
#include <random>

void DrawTileMap()
{
    SDL_Window* window=nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }

    window = SDL_CreateWindow("C++ SDL2 Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 20*16,15*16,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


    SDL_Surface* tile_map_surface = nullptr;
     if (SDL_LoadBMP("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Tiles/tiles.bmp") == NULL) {
         std::cout << "hdwadawhdwD" << std::endl; ;
     }else {
         tile_map_surface = SDL_LoadBMP("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Tiles/tiles.bmp");
         std::cout << "load successfull " << std::endl;
     }

    SDL_Texture* tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);

    SDL_FreeSurface(tile_map_surface);
    srand(time(NULL));

    int tilemap[40][15];
    for (int x = 0; x < 40; x++) {
        for (int y = 0; y < 15; y++) {
            tilemap[x][y] = rand()%4 + 1;
        }
    }

    SDL_Rect tile[20][15];
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 15; y++) {
            tile[x][y].x = x*16;
            tile[x][y].y = y*16;
            tile[x][y].w = 16;
            tile[x][y].h = 16;
        }
    }

    SDL_Rect select_tile_1;
    select_tile_1.x = 0;
    select_tile_1.y = 0;
    select_tile_1.w = 16;
    select_tile_1.h = 16;

    SDL_Rect select_tile_2;
    select_tile_2.x = 16*8;
    select_tile_2.y = 0;
    select_tile_2.w = 16;
    select_tile_2.h = 16;

    SDL_Rect select_tile_3;
    select_tile_3.x = 0;
    select_tile_3.y = 16*8;
    select_tile_3.w = 16;
    select_tile_3.h = 16;

    SDL_Rect select_tile_4;
    select_tile_4.x = 16;
    select_tile_4.y = 16;
    select_tile_4.w = 16;
    select_tile_4.h = 16;

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


        static int offsetX = 0;

        if (keys[SDL_SCANCODE_RIGHT]) {
            offsetX++;
            SDL_Delay(20);
        }
        if (keys[SDL_SCANCODE_LEFT]) {
            offsetX--;
            SDL_Delay(20);
        }
        if (offsetX < 0) {
            offsetX = 0;
        }
        if (offsetX > 39) {
            offsetX = 39;
        }



        // tilemap
        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 15; y++) {

                switch (tilemap[x+offsetX][y]) {
                    case 1:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile_1, &tile[x][y]);
                        break;
                    case 2:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile_2, &tile[x][y]);
                        break;
                    case 3:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile_3, &tile[x][y]);
                        break;
                    case 4:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile_4, &tile[x][y]);
                        break;
                }
            }
        }

        // Draw TextureRect
        SDL_RenderPresent(renderer);
    }






}

#endif //DRAWTILEMAP_H
