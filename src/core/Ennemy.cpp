#include "Ennemy.h"





Ennemy::Ennemy() : Entity(){
    dimension = {0, 0};
    velocity = {0, 0};
    type = SCORPION;
}

Ennemy::Ennemy(int x, int y) : Ennemy(){
    position = {x, y};
}

void Ennemy::changePosition(int x, int y){
    position = {x, y};
}

void Ennemy::moveAuto(){
    int dir = 1;
    for (int i = 0 ; i < 8 ; i++){
        position.x += dir;
        
        if(i > 3)
            dir = -1;
    }


}
