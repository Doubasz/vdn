#ifndef SDLJEU_H
#define SDLJEU_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include "../core/Jeu.h"
#include "../core/Log.h"


#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900

class SDLJeu{

    Jeu jeu;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* background;

    std::vector<SDL_Texture*> playerTexture;
    SDL_Rect playerRect;

    std::vector<SDL_Texture*> platformTexture;
    std::vector<SDL_Rect> plaformRect;

    std::vector<SDL_Texture*> ennemyTexture;
    std::vector<SDL_Rect> ennemyRect;

    Level currentLevel;

    Vec2 camera;

    int state;
    bool quit;


public:
    SDLJeu();

    void gameLoop();
    void input();

    void draw();
    void drawPlayer();
    void drawBackground();

    void loadPlayerTextures();
};


void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& rect);

#endif