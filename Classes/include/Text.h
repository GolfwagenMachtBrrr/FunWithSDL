//
// Created by judelhuu on 7/12/25.
//

#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <SDL2/SDL_ttf.h>
#include <string>

class Text {
public:
    Text(const std::string& filepath, const int& fontsize);
    ~Text();

    void Render(SDL_Renderer* renderer);

    void SetTextRectangle(int x, int y, int width, int height);
    void SetText(const std::string& text);

private:
    SDL_Rect    m_rectangle;
    TTF_Font*   m_font;
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;
    static bool s_ttfInitialized;

    std::string m_text;
};





#endif //TEXTMANAGER_H
