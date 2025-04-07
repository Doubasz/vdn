


#include "Platform.h"


Platform::Platform() : Entity(){
    velocity = {0, 0};
    dimension = {1, 1};
    type = SAND;
    box = Rectangle(0, 0, 1, 1);
}


Platform::Platform(int x, int y) : Platform(){
    position = {x, y};
    box.setX(x);
    box.setY(y);
}

