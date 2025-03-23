#include "Ennemy.h"





Ennemy::Ennemy() : Entity(){
    dimension = {0, 0};
    velocity = {0, 0};
    type = SCORPION;
}

Ennemy::Ennemy(int x, int y) : Ennemy(){
    position = {x, y};
}


void Ennemy::update(){

}