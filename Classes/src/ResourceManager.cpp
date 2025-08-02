//
// Created by judelhuu on 7/6/25.
//

#include "../include/ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager() {
}

ResourceManager::ResourceManager(ResourceManager const &) {
}

ResourceManager ResourceManager::operator=(ResourceManager const &) {
    return *this;
}

// Create an instance of the ResourceManager
ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager* s_instance = new ResourceManager;
    return *s_instance;
}

SDL_Surface * ResourceManager::GetSurface(const std::string& filepath) {
    auto search = m_resources.find(filepath);
    if(search != m_resources.end()){
        return m_resources[filepath];
    }else{
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        m_resources.insert(std::make_pair(filepath,surface));
        return m_resources[filepath];
    }

    return nullptr;
}
