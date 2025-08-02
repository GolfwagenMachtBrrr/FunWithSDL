//
// Created by judelhuu on 8/2/25.
//

#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "nResources.h"
#include <SDL2/SDL.h>

#include <vector>
#include <memory>


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

class MapManager {
public:
    static MapManager& GetInstance() {
        static auto* instance = new MapManager;
        return *instance;
    }



private:

    MapManager();
};



#endif //MAPMANAGER_H
