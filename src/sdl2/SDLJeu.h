#ifndef SDLJEU_H
#define SDLJEU_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <fstream>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <cassert>
#include <thread>
#include "../core/Jeu.h"
#include "../core/Camera.h"
#include "../core/Timer.h"  // Jai ajouté ca 
#include "Button.h"

#include "MenuState.h"
#include "InGameState.h"


#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900


const std::string PLAYER_TEXTURE[13] = {
    "textures/player.png",
    "textures/pebble.png",
};





class SDLJeu{

    SDL_Window* window;
    SDL_Renderer* renderer;

    TTF_Font* font;

    std::unique_ptr<GameState> currentState;
    GameState::StateCode lastState;
    GameState::StateCode currentStateCode;

    bool quit;

public:

    SDLJeu();
    ~SDLJeu();

    void loadFont();
    bool isQuit() const { return quit; }
    void run();

    void loadState(GameState::StateCode state);
};

#endif