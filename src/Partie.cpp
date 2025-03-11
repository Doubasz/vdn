

#include "Partie.h"



Partie::Partie(){

    niveau = DESERT;
    score = 0;
    nbLife = 5;
    isFini = false;
    
}


Partie::Partie(int lvl){

    niveau = lvl;
    player = Player();
    isFini = false;
    nbLife = 5;
    score = 0;

    switch(niveau){
        case DESERT:{
            player.changePosition(Vec2{40, 450});
            
        }

        default:
            break;
    }

}


void Partie::handleInput(SDL_Keycode key){
    switch(key){
        case SDLK_LEFT:
        case SDLK_RIGHT:
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_z:
        case SDLK_q:
        case SDLK_s:
        case SDLK_d:{
            player.seDeplacer(key);
            break;
        }

        case SDLK_SPACE:
            player.sauter();
            break;

        default:
            break;
    }
}


void Partie::draw(SDL_Renderer* renderer){
    player.draw(renderer);
}


void Partie::deroulementPartie(){

    if(isPlayerInTheAir() && !playerOutOfBonds()){
        player.updateGravity();
    }
    else{
        player.resetGravity();
    }
}


bool Partie::isPlayerInTheAir(){

    SDL_Rect playRect = player.getRect();

    for(Decor decor : decors){
        SDL_Rect decrRect = decor.getRect();

        if(SDL_HasIntersection(&playRect, &decrRect)){
            return false;
        }
    }
    return true;
} 

bool Partie::playerOutOfBonds(){
    SDL_Rect playRect = player.getRect();
    return playRect.y + 10 > 900; 
}