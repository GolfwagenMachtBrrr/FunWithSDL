//
// Created by judelhuu on 7/6/25.
//

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SDL2/SDL.h>
#include "ResourceManager.h"

class AnimatedSprite {
public:
    AnimatedSprite(SDL_Renderer*& renderer, const std::string& filepath);
    ~AnimatedSprite();

    void Update();
    void PlayFrame(int x, int y, int width, int heigth, Uint8 frame);
    void Draw(int x, int y, int width, int heigth);
    void Render(SDL_Renderer*& renderer);

private:
    SDL_Rect m_src;
    SDL_Rect m_dst;
    SDL_Texture* m_texture;
};



#endif //ANIMATEDSPRITE_H
