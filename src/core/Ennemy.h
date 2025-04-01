#ifndef ENNEMY_H
#define ENNEMY_H

#include "Entity.h"

enum EnemyType {
    SCORPION,
    SNAKE,
    VULTURE
};

class Ennemy : public Entity {
public:
    Ennemy();
    Ennemy(int x, int y);
    
    void update() override;
    void moveAuto();
    void changePosition(int x, int y);
    
    EnemyType getType() const { return type; }
    void setType(EnemyType newType) { type = newType; }

private:
    EnemyType type;
    int moveCounter = 0; // Pour gérer les mouvements
    bool movingRight = true; // Direction du mouvement
};

#endif