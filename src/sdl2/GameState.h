#ifndef GAME_STATE_H
#define GAME_STATE_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Button.h"


class GameState{
public:

    enum StateCode{
        MAIN_MENU, OPTION, LEVEL, PAUSE, GAME_OVER,
    };

    //virtual ~GameState() {};
    virtual void load() = 0;
    virtual int unload() = 0;
    virtual void handleEvents(SDL_Event& events, float dt) = 0;
    virtual StateCode update(float dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};


#endif