#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "GameState.h"
#include "MenuState.h"

class StateManager{

private:
    GameState* currentState;

public:

    StateManager();
    void run();
};

#endif