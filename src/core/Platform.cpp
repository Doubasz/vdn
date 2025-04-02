


#include "Platform.h"


Platform::Platform() : Entity(){
    velocity = {0, 0};
    dimension = {32, 32};
    type = SAND;
    box = Rectangle(0, 0, 32, 32);
}


Platform::Platform(int x, int y) : Platform(){
    position = {x, y};
    box.setX(x);
    box.setY(y);
}

void Platform::update(){
    
}