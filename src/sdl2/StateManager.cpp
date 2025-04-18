

#include "StateManager.h"



StateManager::StateManager(){

    MenuState* state;
    currentState = state;
}


void StateManager::run(){
    bool quit = false;

    while(!quit){

        float deltaTime = 0.1f;

        GameState::StateCode state = this->currentState->update(deltaTime);

        if(state != GameState::LEVEL){
            //  Nothing for now            
        }

        //this->currentState->render();
    }

}