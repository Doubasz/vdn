


#include "MenuState.h"



MenuState::MenuState(){
    this->renderer = nullptr;
    this->font = nullptr;
}

MenuState::MenuState(SDL_Renderer* renderer, TTF_Font* font){
    this->renderer = renderer;
    this->font = font;
}


void MenuState::load(){

    if(!renderer){
        std::cout << "MenuState::load : renderer is nullptr" << std::endl;
        exit(-1);
    }

    if(!font){
        std::cout << "MenuState::load : font is nullptr" << std::endl;
        exit(-1);
    }

    Button b1 = {300, 300, 200, 50, "start game", SDL_Color{0, 0, 0}, SDL_Color{0, 0, 0}, SDL_Color{0, 0, 0}, SDL_Color{0xFF, 0xFF, 0xFF}, font, renderer};

    // [this]() { runPerft(); };
    b1.setOnClick([this]() {startGame();});

    whatToDoNow = GameState::MAIN_MENU;
    
    buttons.push_back(b1);
}


GameState::StateCode MenuState::startGame(){
    whatToDoNow = GameState::LEVEL;
}

MenuState::~MenuState(){
    delete background;
}


int MenuState::unload(){

}


GameState::StateCode MenuState::update(float dt){
    return whatToDoNow;
}


void MenuState::handleEvents(SDL_Event& events, float deltaTime){
    for(Button& b : buttons){
        b.handleEvent(events);
    }
}


void MenuState::render(SDL_Renderer* renderer) {

    renderBackground(renderer);
    renderButtons(renderer);

    SDL_RenderPresent(renderer);
}


void MenuState::renderButtons(SDL_Renderer* renderer){
    for(Button& b : buttons){
        b.render();
    }
}


void MenuState::renderBackground(SDL_Renderer* renderer){

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);
}