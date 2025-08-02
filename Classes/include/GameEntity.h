//
// Created by judelhuu on 7/6/25.
//

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <SDL2/SDL.h>
#include "Sprite.h"
#include "BoxCollider2D.h"

#include <string>
#include <vector>

#include "nResources.h"

class GameEntity {
public:
    GameEntity();
    GameEntity(SDL_Renderer* renderer, const std::string& name);
    ~GameEntity();

    // Add components
    void AddSpriteComponent(const std::string& spritepath);
    void AddSpriteComponent(const std::string& spritepath, Uint8 redColorKey, Uint8 greenColorKey, Uint8 blueColorKey);
    void AddCollider2DComponent();

    Sprite&              GetSpriteComponent();
    BoxCollider2D&       GetBoxCollider2DComponent(int index);

    void Update();
    void Render();

    void SetPosition(int x, int y);
    void SetDimension(int width, int height) ;

    // ID
    void SetID(Uint64 ID);
    Uint64& GetID();

    // State
    void SetMovementState(SDL_bool state);
    void SetProcessState(SDL_bool state);

    SDL_bool& GetMovementState(); // Entitiy can be either active or passive
    SDL_bool& GetProcessState(); //  Entity can be activated or deactivated, in which case the entity-manager would delete it

    // Layer
    void SetLayer(core::Resources::Layer layer);
    core::Resources::Layer GetLayer();


private:
    std::string m_name;

    Uint64 identifier = -1;
    SDL_bool m_state; SDL_bool m_active;

    Sprite* m_sprite = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    std::vector<BoxCollider2D*> m_colliders;

    // Layer to be Rendered
    core::Resources::Layer m_layer;
};



#endif //GAMEENTITY_H
