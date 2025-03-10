#ifndef JOUEUR_H
#define JOUEUR_H

#include "Draw.h"

enum Etat{
    QAHWA,
    ZETLA,
};


class Joueur{

    SDL_Rect rect;
    SDL_Texture* texture;

    int gravity;
    int velocity;
    int munition;
    int etat;

    public:
        Joueur();

        void sauter();
        void lancerPierre();
        void seDeplacer();
        void draw();

};



#endif