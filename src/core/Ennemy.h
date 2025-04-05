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
    int direction;


public:
    Ennemy();
    Ennemy(int x, int y);

    void changePosition(Vec2 pos);

    void changePosition(int x, int y);

   

    void moveAuto();

    void update() override;

    void deplacement(bool hitwall);
    bool hitWall(Entity & platform);
    bool nextPosVide(Entity &platform);
};

#endif

