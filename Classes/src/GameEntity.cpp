//
// Created by judelhuu on 7/6/25.
//

#include "../include/GameEntity.h"
#include <iostream>

GameEntity::GameEntity() {
    m_sprite = nullptr; // could cause problems with the collider+
    m_renderer = nullptr;
}

GameEntity::GameEntity(SDL_Renderer *renderer, const std::string& name) {
    m_renderer = renderer;
    m_name = name;
}

GameEntity::~GameEntity() {
    if (m_sprite != nullptr) {
        delete m_sprite;
    }

    for (auto collider2D : m_colliders) {
        delete collider2D;
    }
}

void GameEntity::Update() {

}

void GameEntity::Render() {
    if (m_sprite != nullptr) {
        m_sprite->Render(m_renderer);
    }

    for (int i = 0; i < m_colliders.size(); i++) {
        if (m_colliders[i] != nullptr) {
            SDL_SetRenderDrawColor(m_renderer, 255,0,255,SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(m_renderer, &m_colliders[i]->GetColliderBoundingBox());
        }
    }
}

void GameEntity::SetPosition(const int x, const int y) {
    if (m_sprite != nullptr) {
        m_sprite->SetPositon(x,y);
    }
    for (int i = 0; i < m_colliders.size(); i++) {
        if (m_colliders[i] != nullptr) {
            m_colliders[i]->SetPosition(x,y);
        }
    }
}
void GameEntity::SetDimension(int width, int height) {
    if (m_sprite != nullptr) {
        m_sprite->SetDimension(width,height);
    }
    for (int i = 0; i < m_colliders.size(); i++) {
        if (m_colliders[i] != nullptr) {
            m_colliders[i]->SetPosition(width,height);
        }
    }
}

void GameEntity::SetID(Uint64 ID) {
     identifier = ID;
}

 Uint64 & GameEntity::GetID(){
    return identifier;
}

void GameEntity::SetMovementState(SDL_bool state) {
    m_state = state;
}

void GameEntity::SetProcessState(SDL_bool state) {
    m_active = state;
}

SDL_bool & GameEntity::GetMovementState() {
    return m_state;
}

SDL_bool & GameEntity::GetProcessState() {
    return m_active;
}

void GameEntity::SetLayer(core::Resources::UI::Layer layer) {
    m_layer = layer;
}

core::Resources::UI::Layer GameEntity::GetLayer() {
    return m_layer;
}

void GameEntity::AddSpriteComponent(const std::string &spritepath) {
    m_sprite = new Sprite(m_renderer, spritepath);
}
void GameEntity::AddSpriteComponent(const std::string &spritepath, Uint8 redColorKey, Uint8 greenColorKey,
    Uint8 blueColorKey) {
    m_sprite = new Sprite(m_renderer, spritepath, redColorKey, greenColorKey, blueColorKey);
}

void GameEntity::AddCollider2DComponent() {
    m_colliders.push_back(new BoxCollider2D(m_sprite->GetSDLRectPtr()));
}

Sprite& GameEntity::GetSpriteComponent(){
    return *m_sprite;
}


BoxCollider2D& GameEntity::GetBoxCollider2DComponent(const int index) {

    return *m_colliders[index];
}
