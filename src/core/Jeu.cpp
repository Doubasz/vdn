

#include "Jeu.h"
#include "Vec2.h"


Jeu::Jeu(){

    currentLevel = Level(DESERT);
    state = NIVEAU;
}


void Jeu::loadLevel(int level){
    currentLevel.loadLevel(level);
}




void Jeu::gameLoop(){

    
}
int Jeu::getState() const {
    return state;
}
void Jeu::setState(int newState) {
    state = newState;
}
Level& Jeu::getCurrentLevel(){
    return currentLevel;
}

void Jeu::update(std::string input, float deltaTime){
    currentLevel.deroulementLevel(input, deltaTime);
}

