//
// Created by judelhuu on 7/7/25.
//

#ifndef NRESOURCES_H
#define NRESOURCES_H

namespace core
{
    namespace map
    {
        enum RenderType {
            EMPTY = -1,
            DEFAULT = 0,
            IN_SELECTION = 1,
            SELECTED = 2,
        };
    }
    namespace Resources
    {
        enum Layer {
            BACKGROUND = 0,
            MIDDLEGROUND = 1,
            FOREGROUND = 2,
            END
        };

        namespace ID
        {
            enum Textures
            {

            };

            enum Sounds
            {

            };

            enum Fonts
            {

            };
        }

    }

        namespace Entities::ID
        {
            enum Objects
            {
            };

            enum NPC
            {

            };

            enum Items
            {

            };

        }




}

#endif //NRESOURCES_H
