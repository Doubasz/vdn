

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


void Partie::handleInput(const Uint8* key){

    player.seDeplacer(key);

    if(key[SDL_SCANCODE_SPACE]){
        player.sauter();
    }
}


void Partie::draw(SDL_Renderer* renderer){
    player.draw(renderer);
}


void Partie::deroulementPartie(){

    player.update();

    if(!playerOutOfBonds()){
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
    return playRect.y + playRect.h > 700; 
}