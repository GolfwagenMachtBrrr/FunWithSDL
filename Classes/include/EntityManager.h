//
// Created by judelhuu on 7/7/25.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "nResources.h"
#include "GameEntity.h"
#include <memory>
#include <unordered_map>
#include <iostream>

class EntityManager {
public:
    static EntityManager& GetInstance();

    // add/rmv entitiy
    bool CreateEntity(const std::string& name, SDL_Renderer* renderer, core::Resources::UI::Layer layer);
    void RemoveEntity(const std::string &name);

    // retrieve entity
    std::shared_ptr<GameEntity> GetEntity(const std::string& name);
    std::shared_ptr<GameEntity>& GetEntityReference(const std::string& name);


    // Interact with all entities
    void UpdateAll();
    void RenderAllLayers();
    void DeleteAll();

    // Render all entities of a specific layer
    void RenderLayer(core::Resources::UI::Layer layer);

private:
    long long m_entityCount = 0;
    std::unordered_map<std::string, std::shared_ptr<GameEntity>> m_entities;

    EntityManager();
    ~EntityManager() = default;
};



#endif //ENTITYMANAGER_H
