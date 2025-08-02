//
// Created by judelhuu on 7/7/25.
//

#ifndef NUTIL_H
#define NUTIL_H

#include "Classes/include/Vector2.h"
#include "Classes/include/GameEntity.h"
#include <SDL2/SDL.h>


namespace Util
{
     // ------------------------------------Vector struct---------------------------------------------------
     // primitve types
     typedef  Vector2<int>    Vector2i;
     typedef  Vector2<float>  Vector2f;
     typedef  Vector2<Uint32> Vector2u;


     // enum types
     typedef Vector2D_util<core::Resources::ID::Textures, core::Entities::ID::NPC> Vector2_TN;      // Holds DD of n texture and a NPC
     typedef Vector2D_util<core::Resources::ID::Textures, core::Entities::ID::Objects> Vector2_TO;  // Holds ID of a texture and an object
     typedef Vector2D_util<core::Resources::ID::Textures, core::Entities::ID::Items> Vector2_TI;    // Holds ID of a texture and an item


     // user Specific
     typedef Vector2D_util<GameEntity, Uint64> Vector2id;





}


#endif //NUTIL_H
