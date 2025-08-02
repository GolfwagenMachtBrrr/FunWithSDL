//
// Created by judelhuu on 7/7/25.
//

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <SDL2/SDL.h>

#include "Classes/include/GameEntity.h"
#include "CollisionHelper.h"

#include <vector>
#include <memory>

class CollisionManager
{
public:
    static CollisionManager& GetInstance() {
        static CollisionManager* instance = new CollisionManager;
        return *instance;
    }

    void CheckCollesions()
    {
        GetInactiveEntities();

       for (size_t i = 0; i < m_objects.size(); i++) {
          for (size_t j = i + 1; j < m_objects.size(); i++) {

              if (i == j) { continue; }
              if (m_objects[i]->GetBoxCollider2DComponent(0).IsColliding(m_objects[j]->GetBoxCollider2DComponent(0)))
              {
                  auto objectA= m_objects[i]->GetBoxCollider2DComponent(0);
                  auto objectB = m_objects[j]->GetBoxCollider2DComponent(0);

                  objectA.OnCollision(objectB);
                  objectB.OnCollision(objectA);
              }
          }
       }
    }


    SDL_bool AddObject(std::shared_ptr<GameEntity>& object)
    {
        if (object->GetID() == -1) {
            // Last identifier
            //object->SetID();
        }
        if (object->GetProcessState() && !object->GetMovementState()) {
            object->SetMovementState(SDL_TRUE);
        }
        if (!object->GetProcessState()) {
            CollisionInfo::GetInstance().AddInactiveEntity(object->GetID());
           return SDL_FALSE;
        }

        m_objects.push_back(std::move(object));
        return SDL_TRUE;
    }

    void GetInactiveEntities() {
        for (auto& object : m_objects) {
            if (!object->GetProcessState()) {
               CollisionInfo::GetInstance().AddInactiveEntity(object->GetID());
            }
        }
    }


private:
    CollisionManager();
    ~CollisionManager();


    // TODO: 2 Vectoren die sich Buffern
    std::vector<std::shared_ptr<GameEntity>> m_objects;
};



#endif //COLLISIONMANAGER_H
