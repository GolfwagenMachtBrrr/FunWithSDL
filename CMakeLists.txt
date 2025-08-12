cmake_minimum_required(VERSION 3.31)
project(SDL_Tutorial)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_CLASS ./Classes)
set(PROJECT_HEADERS Examples)

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(PNG REQUIRED)
find_package(oatpp-zlib CONFIG REQUIRED)
find_package(zlib-ng CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

include_directories(
        ${CMAKE_SOURCE_DIR}/imgui
        ${CMAKE_SOURCE_DIR}/imgui/include
)

set(IMGUI_SRC
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_demo.cpp
        imgui/backends/imgui_impl_sdl2.cpp
        imgui/backends/imgui_impl_sdlrenderer2.cpp
        Classes/src/Tilemap.cpp
        Classes/include/Tilemap.h
)



add_executable(SDL_Tutorial main.cpp
        ${IMGUI_SRC}
        Examples/DrawOnWindow.h
        Examples/DrawWithShapes.h
        Examples/DrawWithTextureRect.h
        Examples/DrawWithBlender.h
        Examples/DrawWithColorKey.h
        Examples/Example_WaterEffects.h
        Examples/DrawTTFs.h
        Examples/DrawImageFormats.h
        Examples/Example_TexturedRectangles.h
        Classes/src/Sprite.cpp
        Classes/include/Sprite.h
        Classes/src/ResourceManager.cpp
        Classes/include/ResourceManager.h
        Classes/src/AnimatedSprite.cpp
        Classes/include/AnimatedSprite.h
        Examples/DrawAnimatedSprite.h
        Examples/DrawRectangleCollisions.h
        Classes/src/GameEntity.cpp
        Classes/include/GameEntity.h
        Classes/src/BoxCollider2D.cpp
        Classes/include/BoxCollider2D.h
        Classes/src/SDLApp.cpp
        Classes/include/SDLApp.h
        Classes/src/Vector2.cpp
        Classes/include/Vector2.h
        Classes/src/Sound.cpp
        Classes/include/Sound.h
        Classes/src/EntityManager.cpp
        nUtil.h
        Classes/src/CollisionManager.cpp
        Classes/include/CollisionManager.h
        Classes/include/CollisionHelper.h
        Classes/include/EntityManager.h

        nResources.h
        Classes/src/Text.cpp
        Classes/include/Text.h
        Examples/DrawPongGame.h
        Examples/DrawTileMap.h
        Classes/Camera.cpp
        Classes/Camera.h
        Classes/MapManager.cpp
        Classes/MapManager.h
        Examples/DrawImGui.h
)

target_include_directories(SDL_Tutorial PRIVATE
        ${CMAKE_SOURCE_DIR}
)



# Auf Linux reicht SDL2::SDL2 – SDL2main ist nur für Windows nötig
target_link_libraries(SDL_Tutorial PRIVATE
        SDL2::SDL2
)

target_link_libraries(SDL_Tutorial PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)
target_link_libraries(SDL_Tutorial PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
target_link_libraries(SDL_Tutorial PRIVATE PNG::PNG)
target_link_libraries(SDL_Tutorial PRIVATE oatpp::oatpp-zlib)
target_link_libraries(SDL_Tutorial PRIVATE zlib-ng::zlib)
target_link_libraries(SDL_Tutorial PRIVATE $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>)