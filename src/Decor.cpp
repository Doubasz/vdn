


#include "Decor.h"


Decor::Decor(){
    
    rect.x = 50;
    rect.y = 400;
    rect.w = 50;
    rect.h = 100;
}


SDL_Rect Decor::getRect(){
    return rect;
}