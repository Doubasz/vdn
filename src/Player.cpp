


#include "Player.h"


Player::Player(){

    rect.x = 50;
    rect.y = 400;
    rect.w = 50;
    rect.h = 100;

    gravity = 0;
    velocity = 0;
    accel = 1;
    munition = 0;
    etat = 0;

}


void Player::draw(SDL_Renderer* renderer){
    Color color = Color(0xFF523e08);

    drawRect(renderer, rect, color, false);
}



void Player::changePosition(Vec2 pos){
    rect.x = pos.x;
    rect.y = pos.y;
}


void Player::sauter(){
    gravity = -20;
}

void Player::seDeplacer(SDL_Keycode key){

    int level_width = 1000;

    switch(key){
        case SDLK_d:
        case SDLK_RIGHT:{
            if(rect.x < level_width) rect.x += velocity;
            break;
        }
        case SDLK_q:
        case SDLK_LEFT:{
            if(rect.x > 0) rect.x -= velocity;
            break;
        }
    }
}

void Player::updateGravity(){
    rect.y += gravity;
    gravity += 1;
}

void Player::resetGravity(){
    gravity = 0;
}

SDL_Rect Player::getRect(){
    return rect;
}