#include <iostream>
#include "./Constants.h"
#include  "./Game.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
SDL_Renderer* Game::renderer;

Game::Game(){
    this->isRunning = false;
}

Game::~Game(){

}

bool Game::IsRunning() const{
    return this->isRunning;
}
glm::vec2 projectilPos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectilVel = glm::vec2(20.0f, 20.0f);

void Game::Initialize(int width, int height){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if(!window){
        std::cerr << "Error conn la ventana" << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        std::cerr << "Error conn el render" << std::endl;
        return;
    }

    isRunning = true;
    return;
}

void Game::ProcessInput(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:{
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if(event.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            }
        }
        default: {
            break;
        }
    }
    

}
void Game::Update(){

    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;


    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    ticksLastFrame = SDL_GetTicks();

    projectilPos = glm::vec2(
        projectilPos.x + projectilVel.x * deltaTime,
        projectilPos.y + projectilVel.y * deltaTime
    ); 
}
void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_Rect projectile {
        (int)projectilPos.x,
        (int)projectilPos.y,
        10,
        10
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);

    SDL_RenderPresent(renderer);
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
