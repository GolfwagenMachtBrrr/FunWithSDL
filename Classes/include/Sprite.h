//
// Created by judelhuu on 7/6/25.
//

#ifndef TEXTUREDRECTANGLE_H
#define TEXTUREDRECTANGLE_H

#include "SDL2/SDL.h"
#include <string>

class Sprite {
public:
    Sprite(SDL_Renderer* renderer, const std::string& filepath);
    Sprite(SDL_Renderer* renderer, const std::string& filepath, Uint8 redColorKey, Uint8 greenColorKey, Uint8 blueColorKey);

    ~Sprite();

    void Render(SDL_Renderer* renderer);

    void SetPositon(int x, int y);
    void SetDimension(int width, int height);
    void SetColorKey(Uint8 r, Uint8 g, Uint8 b);

    int GetWidth();
    int GetHeight();
    int GetPostionX();
    int GetPostionY();

    Uint8 GetRedKeyColor();
    Uint8 GetGreenKeyColor();
    Uint8 GetBlueKeyColor();


    SDL_Texture* GetSDLTexture();
    SDL_Rect*    GetSDLRectPtr();
    SDL_Rect&    GetSDLRect();



private:
    void InitDefaults();

    SDL_Texture* m_texture;
    SDL_Rect     m_rectangle;

    Uint8 m_redColorKey;
    Uint8 m_greenColorKey;
    Uint8 m_blueColorKey;
};


#endif //TEXTUREDRECTANGLE_H
