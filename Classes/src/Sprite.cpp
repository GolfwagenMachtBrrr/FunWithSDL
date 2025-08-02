//
// Created by judelhuu on 7/6/25.
//

#include "../include/Sprite.h"
#include "../include/ResourceManager.h"
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, const std::string& filepath): m_rectangle() {

    SDL_Surface *retrievedSurface = ResourceManager::GetInstance().GetSurface(filepath);
    SDL_SetColorKey(retrievedSurface, SDL_FALSE, (retrievedSurface->format, m_redColorKey, m_greenColorKey, m_blueColorKey));

    m_texture = SDL_CreateTextureFromSurface(renderer, retrievedSurface);
    SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_ADD);

    InitDefaults();
}

Sprite::Sprite(SDL_Renderer *renderer, const std::string &filepath, Uint8 redColorKey, Uint8 greenColorKey,
    Uint8 blueColorKey) {
    SDL_Surface *retrievedSurface = ResourceManager::GetInstance().GetSurface(filepath);
    // Use the temp available surface to access SetColorKey()
    SDL_SetColorKey(retrievedSurface, SDL_TRUE, (retrievedSurface->format, redColorKey, greenColorKey, blueColorKey));
    m_texture = SDL_CreateTextureFromSurface(renderer, retrievedSurface);

    SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_ADD);

    // Defaults still as a fallback
    InitDefaults();
    m_redColorKey = redColorKey;
    m_greenColorKey = greenColorKey;
    m_blueColorKey = blueColorKey;
}

Sprite::~Sprite() {
    SDL_DestroyTexture(m_texture);
}

SDL_Rect & Sprite::GetSDLRect() {
    return m_rectangle;
}

void Sprite::InitDefaults() {
    // default positions
    m_rectangle.x = 0;
    m_rectangle.y = 0;
    m_rectangle.w = 64;
    m_rectangle.h = 64;

    // default color keys
    m_redColorKey = 0xFF;
    m_greenColorKey = 0;
    m_blueColorKey = 0xFF;
}

void Sprite::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_texture, nullptr, &m_rectangle);
}
void Sprite::SetPositon(const int x, const int y) {
    m_rectangle.x = x;
    m_rectangle.y = y;
}
void Sprite::SetDimension(int width, int height) {
    m_rectangle.w = width;
    m_rectangle.h = height;
}
int Sprite::GetWidth()  {
    return m_rectangle.w;
}
int Sprite::GetHeight()  {
    return m_rectangle.h;
}
int Sprite::GetPostionX()  {
    return m_rectangle.x;
}
int Sprite::GetPostionY()  {
    return m_rectangle.y;

}


SDL_Texture * Sprite::GetSDLTexture() {
    return m_texture;
}

SDL_Rect * Sprite::GetSDLRectPtr() {
    return &m_rectangle;
}





