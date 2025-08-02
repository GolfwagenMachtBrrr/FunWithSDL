//
// Created by judelhuu on 7/13/25.
//

#ifndef DRAWPONGGAME_H
#define DRAWPONGGAME_H

#include "Classes/include/SDLApp.h"
#include "Classes/include/Sound.h"
#include "Classes/include/Text.h"
#include "../Classes/include/EntityManager.h"

#include "nResources.h"

#include <iostream>

// Glöbal
SDLApp* app;

Sound* collisionSound;
Sound* scoreSound;

Text* scorePlayer1;
Text* scorePlayer2;

struct GameState {
    float movementSpeed = NULL;
    float ballSpeed =  NULL;
    float ballXDirection = NULL;
    float ballYDirection = NULL;

    int leftscore = 0, rigthscore = 0;
};

GameState* gamestate;



inline void Pong_HandleEvents() {
    std::shared_ptr<GameEntity> leftpäddle  = EntityManager::GetInstance().GetEntity("Leftpäddle");
    std::shared_ptr<GameEntity> rigthpäddle = EntityManager::GetInstance().GetEntity("rightpäddle");

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app->SetLoop(false);
        }

        if (event.type == SDL_KEYDOWN) {

            if (event.key.keysym.sym == SDLK_UP) {
               rigthpäddle->SetPosition(rigthpäddle->GetSpriteComponent().GetPostionX(), rigthpäddle->GetSpriteComponent().GetPostionY()-gamestate->movementSpeed);
            }

            if (event.key.keysym.sym == SDLK_DOWN) {
                rigthpäddle->SetPosition(rigthpäddle->GetSpriteComponent().GetPostionX(), rigthpäddle->GetSpriteComponent().GetPostionY()+gamestate->movementSpeed);
            }

            if (event.key.keysym.sym == SDLK_w) {
                leftpäddle->SetPosition(leftpäddle->GetSpriteComponent().GetPostionX(), leftpäddle->GetSpriteComponent().GetPostionY()-gamestate->movementSpeed);
            }

            if (event.key.keysym.sym == SDLK_s) {
                leftpäddle->SetPosition(leftpäddle->GetSpriteComponent().GetPostionX(), leftpäddle->GetSpriteComponent().GetPostionY()+gamestate->movementSpeed);
            }


        }
    }
}

inline void Pong_HandleUpdates() {

    std::shared_ptr<GameEntity> leftpäddle  = EntityManager::GetInstance().GetEntity("Leftpäddle");
    std::shared_ptr<GameEntity> rigthpäddle = EntityManager::GetInstance().GetEntity("rightpäddle");
    std::shared_ptr<GameEntity> ball        = EntityManager::GetInstance().GetEntity("ball");

    int ballPositionX = ball->GetSpriteComponent().GetPostionX();
    int ballPositionY = ball->GetSpriteComponent().GetPostionY();

    // Sät boll baundries
    if (ballPositionX > app->GetWindowWidth()-ball->GetSpriteComponent().GetWidth()) {
        scoreSound->PlaySound();
        gamestate->leftscore+=1;
        scorePlayer1->SetText("Left: " + std::to_string(gamestate->leftscore));
        gamestate->ballXDirection*=-1;
    }
    if (ballPositionX < 0) {
        scoreSound->PlaySound();
        gamestate->rigthscore+=1;
        scorePlayer2->SetText("Right: " + std::to_string(gamestate->rigthscore));
        gamestate->ballXDirection*=-1;
    }

    if (ballPositionY > app->GetWindowHeight()-ball->GetSpriteComponent().GetHeight()) {
        gamestate->ballYDirection*=-1;
    }
    if (ballPositionY < 0) {
        gamestate->ballYDirection*=-1;
    }

    if (gamestate->ballXDirection > 0) {
        ballPositionX+=gamestate->ballSpeed;
    }else {
        ballPositionX-=gamestate->ballSpeed;
    }

    if (gamestate->ballYDirection > 0) {
        ballPositionY+=gamestate->ballSpeed;
    }else {
        ballPositionY-=gamestate->ballSpeed;
    }

    ball->SetPosition(ballPositionX, ballPositionY);


    if (leftpäddle->GetBoxCollider2DComponent(0).IsColliding(ball->GetBoxCollider2DComponent(0))) {
        collisionSound->PlaySound();
        std::cout << "*very left kissing noises*" << std::endl;

        gamestate->ballXDirection*=-1;


    }

    if (rigthpäddle->GetBoxCollider2DComponent(0).IsColliding(ball->GetBoxCollider2DComponent(0))) {
        gamestate->ballXDirection*=-1;
        collisionSound->PlaySound();
        std::cout << "*very right kissing noises*" << std::endl;
    }

}

inline void Pong_HandleRendering() {
    std::shared_ptr<GameEntity> leftpäddle  = EntityManager::GetInstance().GetEntity("Leftpäddle");
    std::shared_ptr<GameEntity> rigthpäddle = EntityManager::GetInstance().GetEntity("rightpäddle");
    std::shared_ptr<GameEntity> ball        = EntityManager::GetInstance().GetEntity("ball");
    std::shared_ptr<GameEntity> court       = EntityManager::GetInstance().GetEntity("court");


    court->Render();
    ball->Render();
    leftpäddle->Render();
    rigthpäddle->Render();
    scorePlayer1->Render(app->GetRenderer());
    scorePlayer2->Render(app->GetRenderer());
}

inline void Pong_InitSDLApp() {
    const char* title = "My little Pony";
    app = new SDLApp(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 628);
    app->SetMaxFrameRate(15);

    EntityManager::GetInstance().CreateEntity("Leftpäddle", app->GetRenderer(), core::Resources::Layer::FOREGROUND);
    EntityManager::GetInstance().CreateEntity("rightpäddle", app->GetRenderer(), core::Resources::Layer::FOREGROUND);
    EntityManager::GetInstance().CreateEntity("ball", app->GetRenderer(), core::Resources::Layer::FOREGROUND);
    EntityManager::GetInstance().CreateEntity("court", app->GetRenderer(), core::Resources::Layer::BACKGROUND);

    // Gät se enteties
    std::shared_ptr<GameEntity> leftpäddle  = EntityManager::GetInstance().GetEntity("Leftpäddle");
    std::shared_ptr<GameEntity> rigthpäddle = EntityManager::GetInstance().GetEntity("rightpäddle");
    std::shared_ptr<GameEntity> ball        = EntityManager::GetInstance().GetEntity("ball");
    std::shared_ptr<GameEntity> court       = EntityManager::GetInstance().GetEntity("court");

    court->AddSpriteComponent("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Pong/court.bmp");
    court->SetDimension(app->GetWindowWidth(),app->GetWindowHeight());
    court->SetPosition(0,0);

    leftpäddle->AddSpriteComponent( "/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Pong/leftpaddle.bmp");
    leftpäddle->AddCollider2DComponent();
    leftpäddle->SetDimension(25,200);
    leftpäddle->SetPosition(0, app->GetWindowHeight()-200);


    rigthpäddle->AddSpriteComponent( "/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Pong/rightpaddle.bmp");
    rigthpäddle->AddCollider2DComponent();
    rigthpäddle->SetDimension(25,200);
    rigthpäddle->SetPosition(app->GetWindowWidth()-25, app->GetWindowHeight()-200);

    ball->AddSpriteComponent( "/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Pong/ball.bmp", 255, 255, 255);
    ball->AddCollider2DComponent();
    ball->SetDimension(20,20);
    ball->SetPosition(app->GetWindowWidth()/2, app->GetWindowHeight()/2);


    // grad ned am werkln
    collisionSound = new Sound("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Pong/Collide.wav");
    collisionSound->SetupDevice();

    scoreSound = new Sound("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Pong/Score.wav");
    scoreSound->SetupDevice();

    // Game State
    gamestate = new GameState();
    gamestate->movementSpeed  = 20.0f;
    gamestate->ballSpeed      = 10.0f;
    gamestate->ballXDirection = 1.0f;
    gamestate->ballYDirection = 1.0f;


    //Täxtn
    scorePlayer1 = new Text("Fonts/ExampleFont.ttf", 24);
    scorePlayer1->SetText("Left: " + std::to_string(gamestate->leftscore));
    scorePlayer1->SetTextRectangle(0,0,100,50);

    scorePlayer2 = new Text("Fonts/ExampleFont.ttf", 24);
    scorePlayer2->SetTextRectangle(app->GetWindowWidth()-100,0,100,50);
    scorePlayer2->SetText("Right: " +std::to_string(gamestate->rigthscore));


    app->SetEventCallback(Pong_HandleEvents);
    app->SetUpdateCalback(Pong_HandleUpdates);
    app->SetRenderCalback(Pong_HandleRendering);

    app->RunLoop();

    delete app;
    delete gamestate;

    delete collisionSound;
    delete scoreSound;

    EntityManager::GetInstance().DeleteAll();
}

inline void DrawPong()
{
Pong_InitSDLApp();
}

#endif //DRAWPONGGAME_H
