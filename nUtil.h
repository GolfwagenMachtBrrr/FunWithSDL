//
// Created by judelhuu on 7/7/25.
//

#ifndef NUTIL_H
#define NUTIL_H

#include "Classes/include/Vector2.h"
#include "SDL2/SDL.h"


namespace util
{
     // ------------------------------------Vector struct---------------------------------------------------
     // primitve types
     typedef  Vector2<int>    Vector2i;
     typedef  Vector2<float>  Vector2f;
     typedef  Vector2<Uint32> Vector2u;

     // ImGui
     extern int MyLittleInteger;  // <3
     extern bool MyLittleBoolean;
}


#endif //NUTIL_H
