//
// Created by judelhuu on 7/12/25.
//

#include "../include/Text.h"

Text::Text(const std::string& filepath, const int& fontsize) {
    if(TTF_Init()) {
        //Text::s_ttfInitialized = true;
    }

    m_font = TTF_OpenFont("/home/judelhuu/CLionProjects/SDL_Tutorial/Fonts/ExampleFont.ttf", 32);
}

Text::~Text() {
    SDL_DestroyTexture(m_texture);
    TTF_CloseFont(m_font);
}

void Text::Render(SDL_Renderer *renderer) {
    m_surface = TTF_RenderText_Solid(m_font, m_text.c_str(), {255,255,255});
    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);

    // Free surface memory
    SDL_FreeSurface(m_surface);

    SDL_RenderCopy(renderer, m_texture, nullptr, &m_rectangle);
}

void Text::SetTextRectangle(const int x, const int y, const int width, const int height) {
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = width;
    m_rectangle.h = height;
}

void Text::SetText(const std::string &text) {
    m_text = text;
}

