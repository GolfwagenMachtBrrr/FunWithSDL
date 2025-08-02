//
// Created by judelhuu on 7/7/25.
//

#include "../include/EntityManager.h"


EntityManager & EntityManager::GetInstance() {
    static auto* instance = new EntityManager;
    return *instance;
}

bool EntityManager::CreateEntity(const std::string &name, SDL_Renderer *renderer, core::Resources::Layer layer) {
    std::shared_ptr <GameEntity> newEntity = std::make_shared<GameEntity>(renderer, name);
    newEntity->SetLayer(layer);
    m_entities.insert(std::make_pair(name, newEntity));
    m_entityCount++;
    // Return if Successful
    return (m_entities[name] != nullptr);
}

std::shared_ptr<GameEntity> EntityManager::GetEntity(const std::string &name) {
    return m_entities[name];
}

std::shared_ptr<GameEntity> & EntityManager::GetEntityReference(const std::string &name) {
    return m_entities[name];
}

void EntityManager::RemoveEntity(const std::string &name) {
    const auto found = m_entities.find(name);
    m_entities.erase(found);
    m_entityCount--;
}

void EntityManager::UpdateAll() {
    for (auto&[name, entity] : m_entities) {
        if (entity != nullptr) {
            entity->Update();
        } else {
            std::cout << "Unknown entity Update" << std::endl;
        }
    }
}

void EntityManager::RenderAllLayers() {
    RenderLayer(core::Resources::Layer::BACKGROUND);
    RenderLayer(core::Resources::Layer::MIDDLEGROUND);
    RenderLayer(core::Resources::Layer::FOREGROUND);
}

void EntityManager::DeleteAll() {
    m_entities.erase(m_entities.begin(), m_entities.end());
}

void EntityManager::RenderLayer(core::Resources::Layer layer) {
    for (const auto&[name, entity] : m_entities) {
        if (entity != nullptr && entity->GetLayer() == layer) {
            entity->Render();
        } else {
            std::cout << "Unknown entity render" << std::endl;
        }
    }
}

// Preiwat

EntityManager::EntityManager(): m_entityCount(0) {
}
