//
// Created by judelhuu on 8/2/25.
//

#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "nResources.h"
#include "Classes/include/SDLApp.h"
#include "Classes/include/Sprite.h"


#include <SDL2/SDL.h>
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_sdlrenderer2.h"


#include <vector>
#include <memory>

using namespace core::map;


struct Tile
{
    int tiletype;
    core::map::RenderType rendertype; // 0 default

    bool visible;
    bool copyactive;

    SDL_Rect rectangle;
};

struct Chunk
{
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    bool isDirty = true;
};

struct TileMapinfo // set values when tilemap changes
{
    int tilesize;
    int tilesX, tilesY;
};

class TileMap
{
public:
    TileMap();

    Sprite& GetSprite() {
        return *m_sprite;
    }

    SDL_Rect& GetArea() {
        return m_area;
    }


    void Render(SDL_Renderer* renderer)
    {
        for (int x = 0; x < m_info.tilesX; x++) {
            for (int y = 0; y < m_info.tilesY; y++) {
                const SDL_Rect* tilemap_tile = &m_tilemap[x][y].get()->rectangle;
                const SDL_Rect* grid_tile = m_grid[x][y].get();

                switch (m_tilemap[x][y]->rendertype) // durch enums ersetzen
                {
                    case DEFAULT:
                        SDL_RenderCopy(renderer, m_sprite->GetSDLTexture(), tilemap_tile, grid_tile);
                        break;
                    case IN_SELECTION:
                        SDL_SetTextureColorMod(m_sprite->GetSDLTexture(), 255, 0, 0);
                        SDL_RenderCopy(renderer, m_sprite->GetSDLTexture(), tilemap_tile, grid_tile);
                        SDL_SetTextureColorMod(m_sprite->GetSDLTexture(), 255, 255, 255);
                        break;
                    case SELECTED:
                        SDL_SetTextureColorMod(m_sprite->GetSDLTexture(), 0, 0, 255);
                        SDL_RenderCopy(renderer, m_sprite->GetSDLTexture(), tilemap_tile, grid_tile);
                        SDL_SetTextureColorMod(m_sprite->GetSDLTexture(), 255, 255, 255);
                        break;
                    default:
                        break;
                }
            }
        }
    }



private:
    TileMapinfo m_info;
    SDL_Rect m_area;
    Sprite* m_sprite;

    std::vector<std::vector<std::unique_ptr<Tile>>> m_tilemap;
    std::vector<std::vector<std::unique_ptr<SDL_Rect>>> m_grid;
};



class MapManager {
public:
    static MapManager& GetInstance() {
        if (s_instance == nullptr) {
            s_instance = new MapManager;
        }
        return *s_instance;
    }

    static void Initialize() {
        m_window->SetEventCallback(EventCallback);
        m_window->SetUpdateCalback(UpdateCallback);
        m_window->SetRenderCalback(RenderCallback);

        // Set Sprite
    }

    static void EventCallback()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                m_window->SetLoop(false);
            }
            if (event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&selection_mouseX, &selection_mouseY);

                // relative to camera coords
                center_mouseX = selection_mouseX + camera.x;
                center_mouseY = selection_mouseY + camera.y;

                // mouse is in selection area
                if (selection_mouseX > selectionposX && selection_mouseX < selectionposX+selectionsizeX &&
                    selection_mouseY > selectionposY && selection_mouseY < selectionposY+selectionsizeY)
                {
                    if (selection_mousetileX > 0 && selection_mousetileY > 0) {
                        // reset rendertype to DEFAULT if not SELECTED
                        if (selection_tilemap[selection_mousetileX][selection_mousetileY]->rendertype == IN_SELECTION) {
                            selection_tilemap[selection_mousetileX][selection_mousetileY]->rendertype = DEFAULT;
                        }
                    }

                    // storing indecies of the selected tiles (selection)
                    selection_mousetileX = (selection_mouseX-selectionposX)/tilesize;
                    selection_mousetileY = (selection_mouseY-selectionposY)/tilesize;


                    // Tiles at the stored coords become IN_SELECTION  (SELECTED dont become IN_SELECTION)
                    if (selection_mousetileX > 0 && selection_mousetileX < selectiontiles &&
                        selection_mousetileY > 0 && selection_mousetileY < selectiontiles)
                    {
                        if (selection_tilemap[selection_mousetileX][selection_mousetileY]->rendertype != SELECTED &&
                            selection_tilemap[selection_mousetileX][selection_mousetileY]->visible)
                        {
                            selection_tilemap[selection_mousetileX][selection_mousetileY]->rendertype = IN_SELECTION;
                        }
                    }
                }

                // mouse is in center area
                if (center_mouseX > centerposX && center_mouseX < centerposX+centersizeX &&
                    center_mouseY > centerposY && center_mouseY < centerposY+centersizeY)
                {
                    // if in range
                    if (center_mousetileX >= 0 && center_mousetileX < tilesX &&
                        center_mousetileY >= 0 && center_mousetileY < tilesY)

                    {
                        // reset rendertype to DEFAULT if IN_SELECTION
                        if (center_tilemap[center_mousetileX][center_mousetileY]->rendertype == IN_SELECTION) {
                            center_tilemap[center_mousetileX][center_mousetileY]->rendertype = DEFAULT;
                        }
                    }

                    // storing indecies of the selected tiles (center)
                    center_mousetileX = (center_mouseX-centerposX)/tilesize;
                    center_mousetileY = (center_mouseY-centerposY)/tilesize;

                    // Tiles at the stored coords become IN_SELECTION  (SELECTED dont become IN_SELECTION)
                    if (center_mousetileX >= 0 && center_mousetileX < tilesX &&
                        center_mousetileY >= 0 && center_mousetileY < tilesY)
                    {
                        if (center_tilemap[center_mousetileX][center_mousetileY]->rendertype != SELECTED &&
                            center_tilemap[center_mousetileX][center_mousetileY]->visible)
                        {
                            center_tilemap[center_mousetileX][center_mousetileY]->rendertype = IN_SELECTION;
                        }
                    }
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    std::cout << "CenterX: " << center_mousetileX << " CenterY: " << center_mousetileY <<std::endl;
                    std::cout << "SelectionX: " << selection_mousetileX << " SelectionY: " << selection_mousetileY <<std::endl;


                    // mouse is in SELECTION area
                    if (selection_mouseX > selectionposX && selection_mouseX < selectionposX+selectionsizeX &&
                     selection_mouseY > selectionposY && selection_mouseY < selectionposY+selectionsizeY)
                    {
                        // storing indecies of the selected tiles (selection)
                        savedmousetileX = selection_mousetileX, savedmousetileY = selection_mousetileY;

                        // activate copy mode (selection)
                        selection_tilemap[savedmousetileX][savedmousetileY]->copyactive = true;
                        selection_tilemap[savedmousetileX][savedmousetileY]->rendertype = SELECTED;
                    }

                    // mouse is in CENTER area
                    if (center_mouseX > centerposX && center_mouseX < centerposX+centersizeX &&
                        center_mouseY > centerposY && center_mouseY < centerposY+centersizeY)
                    {
                        // enable visibility
                        center_tilemap[center_mousetileX][center_mousetileY]->visible = true;
                        center_tilemap[center_mousetileX][center_mousetileY]->rendertype = DEFAULT;

                        // assign default tyletype
                        center_tilemap[center_mousetileX][center_mousetileY]->rectangle.x = selection_tiles[0].first;
                        center_tilemap[center_mousetileX][center_mousetileY]->rectangle.y = selection_tiles[0].second;


                        // savedmousetileX must contain a value
                        if (savedmousetileX != -1 && savedmousetileY != -1)
                        {
                            // check wheter copy is active (enabled)
                            if (selection_tilemap[savedmousetileX][savedmousetileY]->copyactive &&
                                center_tilemap[center_mousetileX][center_mousetileY]->copyactive)
                            {
                                // tiletype gets copied
                                center_tilemap[center_mousetileX][center_mousetileY]->tiletype =
                                    selection_tilemap[savedmousetileX][savedmousetileY]->tiletype;

                                center_tilemap[center_mousetileX][center_mousetileY]->rectangle.x =
                                    selection_tiles[center_tilemap[center_mousetileX][center_mousetileY]->tiletype].first;

                                center_tilemap[center_mousetileX][center_mousetileY]->rectangle.y =
                                    selection_tiles[center_tilemap[center_mousetileX][center_mousetileY]->tiletype].second;
                            }
                        }

                    }
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    // deactivate copy mode
                    if (selection_mousetileX > 0 && selection_mousetileX < tilesX &&
                        selection_mousetileY > 0 && selection_mousetileY < tilesY)
                    {
                        selection_tilemap[savedmousetileX][savedmousetileY]->copyactive = false;
                        selection_tilemap[savedmousetileX][savedmousetileY]->rendertype = DEFAULT;
                    }
                }
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_RIGHT:
                        camera.x += tilesize;
                        // Kamera nicht über Tilemap hinaus bewegen
                        if (camera.x > tilesX * tilesize - camera.w)
                            camera.x = tilesX * tilesize - camera.w;
                        break;
                    case SDL_SCANCODE_LEFT:
                        camera.x -= tilesize;
                        if (camera.x < 0) camera.x = 0;
                        break;
                    case SDL_SCANCODE_DOWN:
                        camera.y += tilesize;
                        if (camera.y > tilesY * tilesize - camera.h)
                            camera.y = tilesY * tilesize - camera.h;
                        break;
                    case SDL_SCANCODE_UP:
                        camera.y -= tilesize;
                        if (camera.y < 0) camera.y = 0;
                        break;
                    default:
                        break;
                }
                }
        }
    }
    static void UpdateCallback();
    static void RenderCallback()
    {
         // Set Background color Black
        SDL_SetRenderDrawColor(m_window->GetRenderer(), 0xFF,0xFF,0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_window->GetRenderer());

        // Render ImGui
        static float somefloat = 0;

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello ImGui");
        ImGui::Text("SDL2 Renderer backend");
        ImGui::SliderFloat("float", &somefloat, 0.0f, 1.0f);

        ImGui::Image((ImTextureID)(intptr_t)m_selectionTileMap->GetSprite().GetSDLTexture(), ImVec2(256,256));
        ImGui::End();
        ImGui::Render();

        // Render areas
        SDL_SetRenderDrawColor(m_window->GetRenderer(), 0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(m_window->GetRenderer(), &m_centerTileMap->GetArea());
        SDL_RenderDrawRect(m_window->GetRenderer(), &m_selectionTileMap->GetArea());

        // render selectionmap


        // render tilemap
        for (int x = 0; x < tilesX; ++x) {
            for (int y = 0; y < tilesY; ++y) {
                int tileScreenX = x * tilesize - camera.x + centerposX;
                int tileScreenY = y * tilesize - camera.y + centerposY;

                // Nur rendern, wenn Tile sichtbar im Zentrum (Clipping)
                if (tileScreenX + tilesize < centerposX || tileScreenX > centerposX + centersizeX ||
                    tileScreenY + tilesize < centerposY || tileScreenY > centerposY + centersizeY)
                    continue;

                SDL_Rect src_tile = {
                    selection_tiles[center_tilemap[x][y]->tiletype].first * tilesize,
                    selection_tiles[center_tilemap[x][y]->tiletype].second * tilesize,
                    tilesize,
                    tilesize
                };

                SDL_Rect dst_tile = {
                    tileScreenX,
                    tileScreenY,
                    tilesize,
                    tilesize
                };

                switch (center_tilemap[x][y]->rendertype)
                {
                    case EMPTY:
                        SDL_SetRenderDrawColor(m_window->GetRenderer(), 0,0,0,SDL_ALPHA_OPAQUE);
                        SDL_RenderDrawRect(m_window->GetRenderer(),&dst_tile);
                        break;
                    case DEFAULT:
                        SDL_SetRenderDrawColor(m_window->GetRenderer(), 0,0,0,SDL_ALPHA_OPAQUE);
                        SDL_RenderCopy(m_window->GetRenderer(), m_sprite->GetSDLTexture(), &src_tile, &dst_tile);
                        break;
                    case IN_SELECTION:
                        SDL_SetTextureColorMod(m_sprite->GetSDLTexture(), 255, 0, 0);
                        SDL_RenderCopy(m_window->GetRenderer(), m_sprite->GetSDLTexture(), &src_tile, &dst_tile);
                        SDL_SetTextureColorMod(m_sprite->GetSDLTexture(), 255, 255, 255);
                        break;
                    default:
                        break;
                }
            }
        }
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),m_window->GetRenderer());
        SDL_RenderPresent(m_window->GetRenderer());
    }


private:
    MapManager();

    static TileMap* m_centerTileMap;
    static TileMap* m_selectionTileMap;

    static SDLApp* m_window;
    static MapManager* s_instance;
};



#endif //MAPMANAGER_H
