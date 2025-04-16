


#include "Platform.h"


Platform::Platform() : Entity(){
    velocity = {0, 0};
    type = SAND;
    box = Rectangle(0, 0, 1, 1);
}


Platform::Platform(int x, int y) : Platform(){
    box.setX(x);
    box.setY(y);
}

