


#include "Platform.h"


Platform::Platform() : Entity(){
    velocity = {0, 0};
    dimension = {1, 1};
    type = SAND;
}


Platform::Platform(int x, int y) : Entity(){
    position = {x, y};
}

void Platform::update(){
    
}