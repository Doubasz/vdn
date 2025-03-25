

#include "Jeu.h"
#include "Vec2.h"


Jeu::Jeu(){

    currentLevel = Level(DESERT);
    state = NIVEAU;
}




void Jeu::gameLoop(){

    if(currentLevel.isLevelFinished()){
        currentLevel = Level(currentLevel.getLevel() + 1);
    }
}

Level& Jeu::getCurrentLevel(){
    return currentLevel;
}

void Jeu::handleInput(std::string input){
    currentLevel.deroulementLevel(input);
}


void Jeu::scale(int x){

    currentLevel.scale(x);
}