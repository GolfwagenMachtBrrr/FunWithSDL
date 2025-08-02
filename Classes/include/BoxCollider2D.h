//
// Created by judelhuu on 7/6/25.
//

#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include <SDL2/SDL.h>
#include "Vector2.h"

class BoxCollider2D;

class ICollidor {
public:
    virtual ~ICollidor() = default;
    virtual void OnCollision(BoxCollider2D& otherCollider)=0;
    virtual void Update()=0;
    virtual void Render()=0;
};

class BoxCollider2D : ICollidor{
public:
    BoxCollider2D();
    BoxCollider2D(SDL_Rect* rectangle);
    ~BoxCollider2D()=default;

    void Update() override;
    void Render() override;
    void OnCollision(BoxCollider2D& otherCollider) override;
    void Render(SDL_Renderer* renderer);


    Vector2<int> SetBoundingBoxAutomatically(SDL_Surface* surface, Uint8 redColorKey, Uint8 greenColorKey,Uint8 blueColorKey);

    // Setter Getter
    void SetPosition(int x, int y);
    void SetDimension(int width, int height);

    SDL_Rect& GetColliderBoundingBox();
    SDL_bool IsColliding(BoxCollider2D &otherCollider);
private:
    SDL_Rect* m_colliderRectangle = nullptr;
};



#endif //COLLIDER2D_H
