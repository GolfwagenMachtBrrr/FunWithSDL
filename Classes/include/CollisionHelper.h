//
// Created by judelhuu on 7/7/25.
//

#ifndef COLLISIONHELPER_H
#define COLLISIONHELPER_H

#include "nResources.h"
#include "nUtil.h"

#include <vector>
#include <iostream>

class CollisionInfo
{
public:
    static CollisionInfo& GetInstance() {
        static CollisionInfo* instance = new CollisionInfo;
    }

    void SetLastIdentifiert();
    Uint64* GetLastIdentifier() {return m_lastIdentifier; };


    void AddInactiveEntity(Uint64 identifier) {
        m_deactivatedEntities.push_back(identifier);
    }
    std::vector<Uint64>& GetDeactivatedEntities() {return m_deactivatedEntities;}

private:
    CollisionInfo();
    ~CollisionInfo();

    std::vector<Util::Vector2id> m_NPCs;
    std::vector<Uint64> m_deactivatedEntities;
    Uint64* m_lastIdentifier = nullptr; // latest entity number created by the entity-manager
};

#endif //COLLISIONHELPER_H
