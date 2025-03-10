#ifndef JEU_H
#define JEU_H


#define WIDTH 1400
#define HEIGHT 900


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>

#include "Partie.h"

enum State{
    MENU_PRINCIPALE,
    CHOIX_NIVEAU,
    NIVEAU,
    MENU_NIVEAU,
};


class Jeu{

    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> textures;

    Partie currentPartie;

    int state;
    bool quit;

    public:
        Jeu();

        void gameLoop();
        void draw();
        void input();

};


#endif