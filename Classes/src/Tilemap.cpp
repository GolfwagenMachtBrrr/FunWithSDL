//
// Created by judelhuu on 8/9/25.
//

#include "../include/Tilemap.h"
#include "Classes/MapManager.h"


#include <algorithm>
#include <random>
#include "nUtil.h"


int  util::MyLittleInteger;
bool util::MyLittleBoolean;

using namespace std;

void TileMap::LoadMap(TileMapData* data) {
    for (int x = 0; x < data->tiles.x; x++ )
    {
        std::vector<std::unique_ptr<Tile>> row;
        for (int y = 0; y < data->tiles.y; y++)
        {
            std::unique_ptr<Tile> tile = std::make_unique<Tile>();

            tile->tiletype = rand() % 256;
            tile->rendertype = DEFAULT;

            tile->visible = true;
            tile->copyactive = true;

            tile->rectangle.x = x*data->tilesize + data->area.x;
            tile->rectangle.y = y*data->tilesize + data->area.y;
            tile->rectangle.w = data->tilesize;
            tile->rectangle.h = data->tilesize;

            row.push_back(std::move(tile));
        }
        data->tilemap.push_back(std::move(row));
    }
    cout << data->tilemap.size() << endl;
    cout << "honest work done by (LoadMap)" << endl;
}

void TileMap::LoadMapHelper(TileMapData* data) {

    int tilesX = data->tiles.x;
    int tilesY = data->tiles.y;

    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            int tiletype = y + x * tilesY;
            Vector2i coordinate;

            coordinate.x = x * data->tilesize;
            coordinate.y = y * data->tilesize;

            std::pair<int, Vector2i> token = std::make_pair(tiletype, coordinate);
            coordinates.push_back(token);
        }
    }
    //cout << "honest work done by (LoadMapHelper)" << endl;

}

TileMap::TileMap() {}
TileMap::~TileMap() {}

void TileMap::Initialize(SDL_Renderer *renderer, std::vector<TileMapData> &maptable) {
    LoadTilemapData(maptable);
    LoadSprite(renderer);
    LoadMap(&p_cdata); LoadMap(&p_sdata);

    LoadMapHelper(&p_sdata);
}

Sprite & TileMap::GetSprite() {
    if (m_sprite == nullptr)
        throw std::runtime_error ("warning - sprite not initialized (GetSprite)");
    return *m_sprite;
}
TileMapData * TileMap::GetCData() {
    if (false)
        throw std::runtime_error("warning - tilemapdata not initialized (GetCData)");
    return &p_cdata;
}
TileMapData * TileMap::GetSData() {
    if (false)
        throw std::runtime_error("warning - tilemapdata not initialized (GetSData)");
    return &p_sdata;
}

bool TileMap::CheckTileMapBounds(const Vector2i& value, TileMapData* data) {
    int sizeX = data->tilemap.size();
    int sizeY = data->tilemap.empty() ? 0 : data->tilemap.at(0).size();

   return ((0 <= value.x && 0 <= value.y) && (value.x < sizeX && value.y < sizeY));
}
void TileMap::Render(SDL_Renderer *renderer) {

    SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &p_cdata.area);
    SDL_RenderDrawRect(renderer, &p_sdata.area);

    RenderTileMap(renderer, &p_cdata);
    RenderTileMap(renderer, &p_sdata);
}

void TileMap::RenderTileMap(SDL_Renderer *renderer, TileMapData* data) {
    int tilesize = data->tilesize;   SDL_Rect area = data->area;
    int tilesX = data->tiles.x; int tilesY = data->tiles.y;
    Vector2i tileposition;

    for (int x = 0; x < tilesX; x++) {
        for (int y = 0; y < tilesY; y++) {

            int screenTileX = x * tilesize + area.x;
            int screenTileY = y * tilesize + area.y;

            if (screenTileX + tilesize < area.x || screenTileX > area.x + area.w ||
                screenTileY + tilesize < area.y || screenTileY > area.y + area.h) {
                continue;
            }

            switch (data->uiID)
            {
                case core::Resources::UI::CENTER:
                {
                    // standard
                    int tiletype = data->tilemap[x][y]->tiletype;
                    tileposition = coordinates[tiletype].second;

                    // fill (imgui)
                    if (util::MyLittleBoolean)
                    {
                        tileposition = coordinates[util::MyLittleInteger].second;
                        int neuX = std::clamp(tileposition.x / tilesize, 0, tilesX - 1);
                        int neuY = std::clamp(tileposition.y / tilesize, 0, tilesY - 1);
                        data->tilemap[neuX][neuY]->tiletype = util::MyLittleInteger;
                    }

                    break;
                }

                case core::Resources::UI::SELECTION:
                {
                    int index = y + x*tilesY;
                    tileposition = coordinates[index].second;
                    data->tilemap[x][y]->tiletype = index;

                   // std::cout << index << " : " << tileposition.x << " " << tileposition.y << std::endl;
                    break;
                }

                default:
                    break;
            }

            SDL_Rect src = {
                tileposition.x, // x * data->tilesize
                tileposition.y,
                tilesize,
                tilesize
            };

            SDL_Rect dst = {
                x * tilesize + area.x,
                y * tilesize + area.y,
                tilesize,
                tilesize
            };


            switch (data->tilemap[x][y]->rendertype)
            {
                case EMPTY:
                    break;
                case DEFAULT:
                    SDL_SetRenderDrawColor(renderer, 0,0,0,SDL_ALPHA_OPAQUE);
                    SDL_RenderCopy(renderer, m_sprite->GetSDLTexture(), &src, &dst);
                    break;
                case IN_SELECTION:
                    SDL_SetTextureColorMod(m_sprite->GetSDLTexture(), 255, 0, 0);
                    SDL_RenderCopy(renderer, m_sprite->GetSDLTexture(), &src,  &dst);
                    SDL_SetTextureColorMod(m_sprite->GetSDLTexture(), 255, 255, 255);
                    break;
                case SELECTED:
                    SDL_SetTextureColorMod(m_sprite->GetSDLTexture(), 0, 0, 255);
                    SDL_RenderCopy(renderer, m_sprite->GetSDLTexture(), &src, &dst);
                    SDL_SetTextureColorMod(m_sprite->GetSDLTexture(), 255, 255, 255);
                    break;
                default:
                    break;
            }
        }
    }
}

void TileMap::LoadSprite(SDL_Renderer *renderer) {
    std::string filepath = "/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Tiles/tiles.bmp";
    m_sprite = new Sprite(renderer, filepath, 100,150,200);

    std::cout << "texture loaded " << std::endl;
}

void TileMap::LoadTilemapData(std::vector<TileMapData>& maptables) {
    p_cdata = std::move(maptables.at(0));
    p_sdata = std::move(maptables.at(1));

}
