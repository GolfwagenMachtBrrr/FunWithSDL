//
// Created by judelhuu on 7/6/25.
//

#ifndef RESSOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

class ResourceManager {
private:
    ResourceManager();
    ResourceManager(ResourceManager const&);
    ResourceManager operator=(ResourceManager const&);
public:
    static ResourceManager& GetInstance();
    SDL_Surface* GetSurface(const std::string& filepath);

private:
    std::unordered_map<std::string, SDL_Surface*> m_resources;
};



#endif //RESSOURCEMANAGER_H
