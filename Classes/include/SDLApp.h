//
// Created by judelhuu on 7/6/25.
//

#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL2/SDL.h>
#include <functional>
#include <utility>
#include <set>


class SDLApp {
public:
    SDLApp(const char* title, int x, int y, int width, int height);
    ~SDLApp();

    void RunLoop();

    // Getter Setter

    void SetEventCallback(std::function<void(void)> func);
    void SetUpdateCalback(std::function<void(void)> func);
    void SetRenderCalback(std::function<void(void)> func);

    SDL_Renderer* GetRenderer() const;
    SDL_Window* GetWindow() const;

    int GetMouseX() const;
    int GetMouseY() const;
    int GetWindowWidth() const;
    int GetWindowHeight() const;

    void SetLoop(const bool running);
    void SetMaxFrameRate(int frameRate);

    // Timer
    void AddTimer(Uint32 delay, SDL_TimerCallback callback, void* param);
    Uint32 AddReccuringTimer(Uint32 delay, SDL_TimerCallback callback, void* param);
    void RemoveTimer(SDL_TimerID id);

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    bool m_gameIsRunning = true;
    int m_mouseX, m_mouseY;

    Uint32 m_maxFrameRate; // :  1/60 for 60fps
    uint16_t m_width, m_height;

    std::function<void(void)> m_EventCallback;
    std::function<void(void)> m_UpdateCallback;
    std::function<void(void)> m_RenderCallback;

    std::set<SDL_TimerID> m_timers;
};



#endif //SDLAPP_H
