//
// Created by judelhuu on 7/6/25.
//

#include "../include/AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(SDL_Renderer*& renderer, const std::string& filepath) {
    SDL_Surface* retrievedSurface = ResourceManager::GetInstance().GetSurface(filepath);
    m_texture = SDL_CreateTextureFromSurface(renderer, retrievedSurface);
}

AnimatedSprite::~AnimatedSprite() {
    SDL_DestroyTexture(m_texture);
}

void AnimatedSprite::Update() {
}

void AnimatedSprite::PlayFrame(int x, int y, int width, int heigth, Uint8 frame) {
    m_src.x = x+width*frame; // Adjusted by frame
    m_src.y = y;
    m_src.w = width;
    m_src.h = heigth;
}

void AnimatedSprite::Draw(int x, int y, int width, int heigth) {
    m_dst.x = x;
    m_dst.y = y;
    m_dst.w = width;
    m_dst.h = heigth;
}

void AnimatedSprite::Render(SDL_Renderer *&renderer) {
    if (SDL_RenderCopy(renderer, m_texture, &m_src, &m_dst) != 0) {
        std::cout << "Rendering failed " << SDL_GetError() << std::endl;
    }
}

