#ifndef SDLJEU_H
#define SDLJEU_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
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


#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900


const std::string PLAYER_TEXTURE[13] = {
    "textures/player.png",
    "textures/pebble.png",
};


struct Animation{
    int startFrame;    
    int numFrames;      
    int currentFrame;   
    float frameTime;    
    float timer;     
    bool loop;
};

enum GameState{
    MAIN_MENU, OPTION, LEVEL, GAME_OVER, 
};

class SDLJeu{

    Jeu jeu;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* background;
    SDL_Texture* background1;
    SDL_Texture* tileSet;

    SDL_Texture* playerSheet;
    SDL_Rect playerRect;

    std::vector<Animation> playerAnimation;

    Animation currentAnimation;

    std::vector<SDL_Texture*> platformTexture;
    std::vector<SDL_Rect> plaformRect;

    SDL_Texture* ennemySheet;

    TTF_Font* font;
    SDL_Color textColor;

    Animation ennemyAnimation;


    //std::vector<Button> buttons;


    Camera camera;

    int tileSize;
    int blinkInterval;

    int lastPlayerState;

    int state;
    bool quit;
    Timer gameTimer{1.0};  
    double gameTime;

    Mix_Chunk* sauter;
    Mix_Chunk* gotHit;
    Mix_Chunk* walk;
    Mix_Chunk* attack;
    Mix_Chunk* land;
    Mix_Music* music;

    
    Timer moveTimer;
    Timer attacksound;
    GameState gameState = MAIN_MENU; // Valeur par défaut : le menu


public:

    SDLJeu();
    ~SDLJeu();


    void gameLoop();
    void input(float deltaTime);

    void draw();
    void drawPlayer();
    void drawEnnemy();
    void drawTiles();
    void drawBackground();
    void drawLives(); 
    void drawTimer();

    void renderMainMenu();

    void update(float deltaTime);

    void loadPlayerTextures();
    void loadPlatformTextures();
    void loadTextures();
    int loadSounds(int niveau);

    int playBackgroundMusic(int niveau, int state);

    void loadFont();

    void loadAnimations();
    void playSound(std::string input);
    void updateAnimation(float deltaTime);
    void updateEnnemyAnimation(float deltaTime);
    void setAnimation(int playerAnim);
    bool isQuit() const { return quit; }

};


SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path);
void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& rect);
void drawRect(SDL_Renderer*& renderer, SDL_Rect& rect, SDL_Color color);


#endif