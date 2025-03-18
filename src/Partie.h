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

#define HAUTEURINIT 3
class Partie{

    int niveau;
    int score;
    int nbLife;
    bool isFini;
    
 

    Player player;
    std::vector<Ennemi> ennemies;
    std::vector<Decor> decors;
    

    public:
        Partie();
        Partie(int lvl);

        void checkCollision();
        void deroulementPartie();
        void handleInput(const char key);
        bool isPlayerInTheAir();
        bool playerOutOfBonds();
};


#endif