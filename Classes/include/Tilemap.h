//
// Created by judelhuu on 8/9/25.
//

#ifndef TILEMAP_H
#define TILEMAP_H

#include "SDL2/SDL.h"
#include "Classes/include/Sprite.h"
#include "nResources.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace core;
using namespace util;
using namespace core::map;


class TileMap
{
public:
    TileMap();
    ~TileMap();

    void Initialize(SDL_Renderer* renderer, std::vector<TileMapData>& maptable);

    void Render(SDL_Renderer *renderer);
    void RenderTileMap(SDL_Renderer *renderer, TileMapData* data);

    void LoadMap(TileMapData* data );
    void LoadMapHelper(TileMapData* data );
    void LoadSprite(SDL_Renderer* renderer);
    void LoadTilemapData(std::vector<TileMapData>& maptables);

    bool _loaded = false;

    Sprite& GetSprite();

    TileMapData* GetCData();
    TileMapData* GetSData();
    std::vector<std::pair<int, util::Vector2i>>& GetTileCoords() {
        return coordinates;
    }



    bool CheckTileMapBounds(const Vector2i& value, TileMapData* data);

private:
    Sprite*     m_sprite;
    std::vector<TileMapData> m_dataTables;

private:
    TileMapData p_cdata;
    TileMapData p_sdata;
    std::vector<std::pair<int, util::Vector2i>> coordinates;
};



#endif //TILEMAP_H
