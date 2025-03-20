

#include "Partie.h"



Partie::Partie(){

    score = 0;

    nbLife = 5;
    isFini = false;
    player = Player();
}





void Partie::handleInput(const char key,const Niveau &n){

    player.seDeplacer(key,n);

    if(key == ' '){
        player.sauter();
    }
}

Player& Partie::getPlayer(){
    return player;
}

vector<Niveau> Partie::getNiveaux() {
    return niveaux;
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

