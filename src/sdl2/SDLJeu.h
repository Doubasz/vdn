#ifndef SDLJEU_H
#define SDLJEU_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <fstream>

#include <vector>
#include "../core/Jeu.h"
#include "../core/Log.h"
#include "../core/Camera.h"


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


    Camera camera;

    int tileSize;
    int blinkInterval;

    int lastPlayerState;

    int state;
    bool quit;


public:
    SDLJeu();
    ~SDLJeu();

    void scale();

    void gameLoop();
    void input(float deltaTime);

    void draw();
    void drawPlayer();
    void drawEnnemy();
    void drawTiles();
    void drawBackground();
    void drawLives(); 

    void update(float deltaTime);

    void loadPlayerTextures();
    void loadPlatformTextures();
    void loadTextures();
    void loadFont();

    void loadAnimations();
    void updateAnimation(float deltaTime);
    void updateEnnemyAnimation(float deltaTime);
    void setAnimation(int playerAnim);
};


SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path);
void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& rect);
void drawRect(SDL_Renderer*& renderer, SDL_Rect& rect, SDL_Color color);


#endif