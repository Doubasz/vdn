#ifndef RENDER_JEU_H
#define RENDER_JEU_H


#include <SDL2/SDL.h>
#include <vector>

#include "Partie.h"
#include "Draw.h"

#define WIDTH 1400
#define HEIGHT 900


enum State{
    MENU_PRINCIPALE,
    CHOIX_NIVEAU,
    NIVEAU,
    MENU_NIVEAU,
};


class RenderJeu{

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* background;
    SDL_Texture* playerTexture;

    std::vector<SDL_Texture*> gameBgTexture;
    std::vector<SDL_Texture*> decorTexture;
    std::vector<SDL_Texture*> ennemyTexture;

    SDL_Rect playerRect;
    std::vector<SDL_Rect> ennemyRect;
    std::vector<SDL_Rect> decorRect;

    Partie currentPartie;
    Player player;

    bool quit;
    int state;

    public:
        RenderJeu();

        void draw();
        void input();
        void gameLoop();

        void drawPlayer();
        void drawPartie();

        void partieHandleInput();
        void playerMouvement(const Uint8* key)

};



#endif