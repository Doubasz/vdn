#ifndef JEU_H
#define JEU_H


#include <vector>
#include <iostream>

#include "Partie.h"
#include "Niveau.h"

enum State{
    MENU_PRINCIPALE,
    CHOIX_NIVEAU,
    NIVEAU,
    MENU_NIVEAU,
};


class Jeu{

    
    Partie currentPartie;

    int state;
    bool quit;

    public:
        Jeu();

        void actionAuto();

        void gameLoop();
        void draw();
        void input();

};


#endif