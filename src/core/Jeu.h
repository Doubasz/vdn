#ifndef JEU_H
#define JEU_H


#include <vector>
#include <iostream>

#include "Level.h"

enum State{
    MENU_PRINCIPAL,
    CHOIX_NIVEAU,
    NIVEAU,
    MENU_NIVEAU,
};


class Jeu{


    Level currentLevel;
    int state;

    public:

        Jeu();
        void gameLoop();

        int getState() const;

        void setState(int newState);

        void loadLevel(int level);

        Level& getCurrentLevel();
        void update(std::string input, float deltaTime);

};


#endif