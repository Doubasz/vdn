#ifndef ENNEMY_H
#define ENNEMY_H


#include "Entity.h"
#include "Timer.h"

enum TypeEnnemy{
    SCORPION,
    BATARD,

};

class Ennemy : public Entity{

private:
    int direction;    
    int type;
    float gravity;
    float maxFall;
    int state;
 
    Timer move;


public:
    Ennemy();
    Ennemy(int x, int y,int typeEnnemy);

    void changePosition(Vec2 pos);

    void changePosition(int x, int y);

   void changeDirection();

    void moveAuto();
    void update(float deltaTime);

    void deplacement(bool hitwall);
    int getType() const;
    bool PlayerOutofRange(Entity &player)const;
    void followPlayer(Entity &player);
    bool hitWall(Entity &platform);
    bool vaTomber(std::vector<std::vector<int>> &gameMap) ;
    bool nextPosVide(Entity &platform);

    int getDirection(){return direction;}
};

#endif

