#include <SDL2/SDL.h>

#include <imgui/imgui.h>
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_sdlrenderer2.h"

#include "Classes/MapManager.h"

int main() {
    MapManager::GetInstance().Initialize();


    return 0;
}

