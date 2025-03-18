

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


void Partie::handleInput(const char key){

    player.seDeplacer(key);

    if(key == ' '){
        player.sauter();
    }
}




/*void Partie::deroulementPartie(){

    player.update();

    if(!playerOutOfBonds()){
        player.updateGravity();
    }
    else{
        player.resetGravity();
    }
}*/


bool Partie::isPlayerInTheAir(){

    Vec2 playPos = player.getPos();
    return false;
} 

