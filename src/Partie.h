#ifndef PARTIE_H
#define PARTIE_H


#include "Joueur.h"
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

    Joueur joueur;
    std::vector<Ennemi> ennemies;
    std::vector<Decor> decors;
    

    public:
        Partie();
        void draw();
        void checkCollision();
        void deroulementPartie();

};

#endif