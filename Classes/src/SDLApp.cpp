//
// Created by judelhuu on 7/6/25.
//

#include "../include/SDLApp.h"

SDLApp::SDLApp(const char *title, int x, int y, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    m_window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    m_width = width, m_height = height;
}

SDLApp::~SDLApp() {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDLApp::RunLoop() {
    while (m_gameIsRunning) {
        Uint32 startTime = SDL_GetTicks();
        SDL_GetMouseState(&m_mouseX, &m_mouseY);

        m_EventCallback();
        m_UpdateCallback();
        m_RenderCallback();

        Uint32 elapsedTime = SDL_GetTicks64() - startTime;
        if (elapsedTime < m_maxFrameRate) {
            SDL_Delay(m_maxFrameRate - elapsedTime);
        };
    }
}

void SDLApp::SetEventCallback(std::function<void()> func) {
    m_EventCallback = func;
}

void SDLApp::SetUpdateCalback(std::function<void()> func) {
    m_UpdateCallback = func;
}

void SDLApp::SetRenderCalback(std::function<void()> func) {
    m_RenderCallback = func;
}

SDL_Renderer * SDLApp::GetRenderer() const {
    return m_renderer;
}

SDL_Window * SDLApp::GetWindow() const {
    return m_window;
}

int SDLApp::GetMouseX() const {
   return m_mouseX;
}

int SDLApp::GetMouseY() const {
    return m_mouseY;
}

int SDLApp::GetWindowWidth() const {
    return m_width;
}

int SDLApp::GetWindowHeight() const {
    return m_height;
}

void SDLApp::SetLoop(const bool running) {
    m_gameIsRunning = running;
}

void SDLApp::SetMaxFrameRate(int frameRate) {
    m_maxFrameRate = frameRate;
}

void SDLApp::AddTimer(Uint32 delay, SDL_TimerCallback callback, void *param) {
    SDL_TimerID id = SDL_AddTimer(delay, callback, param);
    m_timers.insert(id);
}

Uint32 SDLApp::AddReccuringTimer(Uint32 interval, SDL_TimerCallback callback, void *param) {
    SDL_TimerID id = SDL_AddTimer(interval, callback, param);
    m_timers.insert(id);

    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = nullptr;
    userevent.data2 = nullptr;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);

    return interval;
}

void SDLApp::RemoveTimer(SDL_TimerID id) {
    SDL_RemoveTimer(id);
    m_timers.erase(id);
}
