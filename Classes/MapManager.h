//
// Created by judelhuu on 8/2/25.
//

#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "nResources.h"
#include "nUtil.h"

#include "Classes/include/SDLApp.h"
#include "Classes/include/Sprite.h"
#include "Classes/include/Tilemap.h"



#include <SDL2/SDL.h>
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_sdlrenderer2.h"

#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace core;
using namespace util;


class MapManager {
public:
    static MapManager& GetInstance() {
       static MapManager instance;
       return instance;
    }
    SDLApp* GetAppHandle() {
        return m_window;
    }

     void EventCallback()
     {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                m_window->SetLoop(false);
            }
            Update(event, m_tilemap.GetSData()); // maybe not se best plazze
            Update(event, m_tilemap.GetCData());
        }

     }

     void RenderCallback() {
        SDL_RenderClear(m_window->GetRenderer());

        RenderImGui();
        m_tilemap.Render(m_window->GetRenderer());

        SDL_RenderPresent(m_window->GetRenderer());
    }
     void UpdateCallback() {
    }

    void Initialize() {
        const char* title = "Graphix";
        m_window = new SDLApp(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1920, 1080);
        m_window->SetMaxFrameRate(10);

        SetupImGui();
        SetupTileMap();
        
        // Setup Callbacks
        m_window->SetEventCallback(std::bind(&MapManager::EventCallback,this));
        m_window->SetUpdateCalback(std::bind(&MapManager::UpdateCallback,this));
        m_window->SetRenderCalback(std::bind(&MapManager::RenderCallback,this));
        m_window->RunLoop();
    }
    void Update(SDL_Event &event, TileMapData *data) {
        // ..................................................................

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        data->inputdata.mouse.x = mouseX;
        data->inputdata.mouse.y = mouseY;

        if (IsMouseWithinAreaBounds(data))
            if (data->tilemap[data->inputdata.tile.x][data->inputdata.tile.y]->rendertype == IN_SELECTION)
                data->tilemap[data->inputdata.tile.x][data->inputdata.tile.y]->rendertype = DEFAULT;

        int _selectedX = (data->inputdata.tile.x = (mouseX - data->area.x) / data->tilesize);
        int _selectedY = (data->inputdata.tile.y = (mouseY - data->area.y) / data->tilesize);

        // ..................................................................

        if (event.type == SDL_MOUSEMOTION) {
            CheckMouseBounds(data, _selectedX, _selectedY);
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            CheckTextureUpdates(event, data, _selectedX, _selectedY);
        }
    }

private:
    void CheckMouseBounds(TileMapData* data, int x, int y) // pick either datapack :D
    {
        if (IsMouseWithinAreaBounds(data))
        {
             if (data->tilemap[x][y]->rendertype != SELECTED) {
                 data->tilemap[x][y]->rendertype = IN_SELECTION;
             }
        }
    }

    void CheckTextureUpdates(SDL_Event &event, TileMapData* data, int x, int y)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (IsMouseWithinAreaBounds(data))
            {
                if (data->uiID == core::Resources::UI::UIType::SELECTION)
                {
                    // reset earlier selection
                    ResetUserInput();

                    // copy
                    data->tilemap[x][y]->rendertype = SELECTED;

                    // save tiletype & location
                    data->inputdata.tiletype = data->tilemap[x][y]->tiletype;
                    data->inputdata.tile_selected = Vector2i(x,y);

                }

                if (data->uiID == core::Resources::UI::UIType::CENTER)
                {
                    // where is a better solution?
                    if (m_tilemap.GetSData()->inputdata.tiletype != -1) {
                        data->tilemap[x][y]->tiletype = m_tilemap.GetSData()->inputdata.tiletype;
                    }

                }
            }
        }

        if (event.button.button == SDL_BUTTON_RIGHT)
        {
            ResetUserInput();
        }
    }

    bool IsMouseWithinAreaBounds(TileMapData* data) {
        if (m_tilemap.CheckTileMapBounds(data->inputdata.tile, data)) {
            return (data->inputdata.mouse.x > data->area.x && data->inputdata.mouse.x < data->area.x+data->area.w &&
                    data->inputdata.mouse.y > data->area.y && data->inputdata.mouse.y < data->area.y+data->area.h);
        }
        return false;
    }
    void ResetUserInput()
    {
        TileMapData* data = m_tilemap.GetSData();

        // default values (ssss)
        data->inputdata.rendertype = DEFAULT;

        if (data->inputdata.tile_selected == Vector2i(-1,-1)) {
            std::cout << "the system works" << std::endl;
            return; // can I return a comment?
        }

        // reset last selected
        data->tilemap.at(data->inputdata.tile_selected.x).at(data->inputdata.tile_selected.x)->rendertype = DEFAULT;
        data->inputdata.tile_selected = Vector2i(-1,-1);
    }

    void SetupImGui() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui::StyleColorsClassic();
        ImGui_ImplSDL2_InitForSDLRenderer(m_window->GetWindow(), m_window->GetRenderer());
        ImGui_ImplSDLRenderer2_Init(m_window->GetRenderer());


    }
    void SetupTileMap() {
        TileMapData cdata; // setup selection % center ...
        TileMapData sdata;

        sdata.textureID = core::Resources::ID::TEST;
        sdata.uiID = core::Resources::UI::UIType::SELECTION;
        cdata.textureID = core::Resources::ID::TEST;
        cdata.uiID = core::Resources::UI::UIType::CENTER;

        cdata.tilesize = 16;
        cdata.tiles = Vector2i(1024 / 16, 528 / 16);
        cdata.area = SDL_Rect{
            // magic
            (m_window->GetWindowWidth() - 1024) / 2,
            (m_window->GetWindowHeight() - 528) / 2,
            1024,
            528
        };

        sdata.tilesize = 16;
        sdata.tiles = Vector2i(256 / 16, 256 / 16);
        sdata.area = SDL_Rect{
            // magic
            0,
            0,
            256,
            256
        };

        std::vector<TileMapData> dataTable;
        dataTable.push_back(std::move(cdata));
        dataTable.push_back(std::move(sdata));

        m_tilemap.Initialize(m_window->GetRenderer(), dataTable);
    }
    void RenderImGui() {
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Hello ImGui");
        ImGui::Text("Fill me Baby");
        ImGui::Checkbox("Fill", &util::MyLittleBoolean);
        ImGui::SliderInt("tiletype", &util::MyLittleInteger, 0, 255);

        ImGui::Image((ImTextureID) (intptr_t) m_tilemap.GetSprite().GetSDLTexture(), ImVec2(256, 256));
        ImGui::End();
        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_window->GetRenderer());
    }

private:
    static MapManager* s_instance;

    SDLApp*     m_window;
    TileMap     m_tilemap;


    MapManager() {
    }
    ~MapManager() {
    }
};





#endif //MAPMANAGER_H
