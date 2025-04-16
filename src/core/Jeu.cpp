

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
int Jeu::getState() const {
    return state;
}
void Jeu::setState(int newState) {
    state = newState;
}
Level& Jeu::getCurrentLevel(){
    return currentLevel;
}

void Jeu::handleInput(std::string input, float deltaTime){
    currentLevel.deroulementLevel(input, deltaTime);
}

