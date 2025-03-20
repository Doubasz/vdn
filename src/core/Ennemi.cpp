#include "Ennemi.h"





Ennemi::Ennemi(){

x=1;


y=1; 

dir=0;

}

int Ennemi::getX() const {
    return x;
}

void Ennemi::setX(int newX) {
    x = newX;
}

int Ennemi::getY() const {
    return y;
}

void Ennemi::setY(int newY) {
    y = newY;
}

int Ennemi::getDir() const {
    return dir;
}

void Ennemi::setDir(int newDir) {
    dir = newDir;
}




