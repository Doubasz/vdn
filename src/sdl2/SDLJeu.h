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
#include "../core/Log.h"
#include "../core/Camera.h"
#include "../core/Timer.h"  // Jai ajouté ca 
#include "Button.h"

#include "GameState.h"
#include "MenuState.h"
#include "InGameState.h"


#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900


const std::string PLAYER_TEXTURE[13] = {
    "textures/player.png",
    "textures/pebble.png",
};





class SDLJeu{

    Jeu jeu;

    SDL_Window* window;
    SDL_Renderer* renderer;


    TTF_Font* font;
    SDL_Color textColor;



    std::vector<Button> buttons;

    std::unique_ptr<GameState> currentState;
    GameState::StateCode lastState;
    GameState::StateCode currentStateCode;


    int state;
    bool quit;
    Timer gameTimer{1.0};  
    double gameTime;

   

    
    

    bool pKeyWasPressed = false; 

    SDL_Rect quitButtonRect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50, 200, 60};



public:

    SDLJeu();
    ~SDLJeu();


    void drawLives(); 
    void drawTimer();

    void renderMainMenu();

    int loadSounds(int niveau);

    int playBackgroundMusic(int niveau, int state);

    void loadFont();

    void playSound(std::string input);
    bool isQuit() const { return quit; }
    void resetGame();


    void run();

    GameState* loadState(GameState::StateCode state);
};



void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& rect);
void drawRect(SDL_Renderer*& renderer, SDL_Rect& rect, SDL_Color color);


#endif