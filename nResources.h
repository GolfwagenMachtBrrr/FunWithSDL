//
// Created by judelhuu on 7/7/25.
//

#ifndef NRESOURCES_H
#define NRESOURCES_H

#include "nUtil.h"
#include <vector>
#include <memory>


namespace core
{
    namespace Input {
        namespace MapInput
        {
            struct InputData
            {
                util::Vector2i mouse{};
                util::Vector2i tile{};
                util::Vector2i tile_selected = util::Vector2i(-1,-1);

                int tiletype = -1;
                int rendertype = -1;
            };
        }

    }


    namespace Resources
    {
        namespace UI {
            enum Layer {
                BACKGROUND = 0,
                MIDDLEGROUND = 1,
                FOREGROUND = 2,
                END
            };

            enum UIType {
                UNDEFINED = -1,
                SELECTION,
                CENTER, // Warum center !?!?!?! (more windows will kill me)
            };
        }


        namespace ID
        {
            enum Textures
            {
                UNDEFINED = -1,
                TEST,
            };

            enum Sounds
            {

            };

            enum Fonts
            {

            };
        }

    }

    namespace map
    {
        enum RenderType {
            EMPTY = -1,
            DEFAULT = 0,
            IN_SELECTION = 1,
            SELECTED = 2,
        };

        struct Tile
        {
            void Enable(const util::Vector2i& position, const util::Vector2i& tilesize) {
                rendertype = RenderType::DEFAULT;

                visible = true;

                rectangle = {
                    position.x,
                    position.y,
                    tilesize.x,
                    tilesize.y
                };
            }

            // ID
            int        tiletype   = 0;
            RenderType rendertype = RenderType::EMPTY;

            // Data
            bool visible = false;
            bool copyactive = false;
            SDL_Rect rectangle;
        };

        struct TileMapData
        {
            // ID
            Resources::ID::Textures textureID = Resources::ID::Textures::UNDEFINED;
            Resources::UI::UIType   uiID      = Resources::UI::UIType::UNDEFINED;

            // Data
            int tilesize;
            int offsetX = 0, offsetY = 0;
            int rangeX, rangeY;
            float zoom = 1.0f;

            util::Vector2i tiles; // amount
            SDL_Rect area;

            // storing input data
            core::Input::MapInput::InputData inputdata;

            // tile data
            std::vector<std::vector<std::unique_ptr<core::map::Tile>>> tilemap;
        };
    }

    namespace Entities::ID {
        enum Objects {
        };

        enum NPCs {
        };

        enum Items {
        };
    }

}

#endif //NRESOURCES_H
