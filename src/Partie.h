#ifndef PARTIE_H
#define PARTIE_H


#include "Player.h"
#include "Ennemi.h"
#include "Decor.h"

enum Niveau{
    DESERT,
    FORET,
    VILLE
};

class Partie{

    int niveau;
    int score;
    int nbLife;
    bool isFini;
    
    SDL_Texture* background;

    Player player;
    std::vector<Ennemi> ennemies;
    std::vector<Decor> decors;
    

    public:
        Partie();
        Partie(int lvl);

        void draw(SDL_Renderer* renderer);
        void checkCollision();
        void deroulementPartie();
        void handleInput(SDL_Keycode key);
        bool isPlayerInTheAir();
        bool playerOutOfBonds();
};


#endif