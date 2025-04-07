#ifndef ENNEMY_H
#define ENNEMY_H


#include "Entity.h"
#include "Timer.h"

enum TypeEnnemy{
    SCORPION,
    KALB,
};

class Ennemy : public Entity{

private:    
    int type;
    float gravity;
    int state;
 
    Timer move ;


public:
    Ennemy();
    Ennemy(int x, int y);

    void changePosition(Vec2 pos);

    void changePosition(int x, int y);

   void changeDirection();

    void moveAuto();

    void update() override;

    void deplacement(bool hitwall);
    bool hitWall(Entity & platform);
    bool vaTomber(std::vector<std::vector<int>> &gameMap) ;
    bool nextPosVide(Entity &platform);
};

#endif

