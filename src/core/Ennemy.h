#ifndef ENNEMY_H
#define ENNEMY_H


#include "Entity.h"

enum TypeEnnemy{
    SCORPION,
    KALB,
};

class Ennemy : public Entity{

private:    
    int type;
    float gravity;
    int state;


public:
    Ennemy();
    Ennemy(int x, int y);

    void changePosition(int x, int y);

    void moveAuto();


};



#endif

