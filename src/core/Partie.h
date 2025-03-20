#ifndef PARTIE_H
#define PARTIE_H


#include "Player.h"
#include "Ennemi.h"
#include "Niveau.h"


enum Niveauu{
    DESERT,
    FORET,
    VILLE
};

class Partie{

    int niveau;
    int score;
    int nbLife;
    bool isFini;
    
    vector<Niveau> niveaux;
 

    Player player;


    public:
        Partie();
        Partie(int lvl);
        vector<Niveau> getNiveaux();
        void checkCollision();
        void deroulementPartie();
        void handleInput(const char key,const Niveau &n);
        Player& getPlayer();
        bool isPlayerInTheAir();
        bool playerOutOfBonds();
        int getPlayerState();
};


#endif