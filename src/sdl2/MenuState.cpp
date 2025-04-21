


#include "MenuState.h"



MenuState::MenuState(){
    this->renderer = nullptr;
    this->font = nullptr;

    state = WindowStat::NORMAL;
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

    loadTextures();
    initButtons();

    whatToDoNow = GameState::MAIN_MENU;

    load_music();

}


void MenuState::initButtons(){

    int screenWidth = 1400;

    int buttonWidth = 400;
    int buttonHeight = 100;

    Button b1 = {(screenWidth / 2) - (buttonWidth / 2), 350, buttonWidth, buttonHeight, "Start game", SDL_Color{0, 0, 0, 255}, SDL_Color{200, 100, 20, 255}, SDL_Color{50, 100, 50, 255}, SDL_Color{0xFF, 0xFF, 0, 255}, font, renderer};
    // [this]() { runPerft(); };
    b1.setOnClick([this]() {startGame();});

    Button b2 = {(screenWidth / 2) - (buttonWidth / 2), 500, buttonWidth, buttonHeight, "Levels", SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{0xFF, 0xFF, 0xFF, 255}, font, renderer};
    b2.setOnClick([this]() {chooseLevel();});

    Button b3 = {(screenWidth / 2) - (buttonWidth / 2), 650, buttonWidth, buttonHeight, "Options", SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{0xFF, 0xFF, 0xFF, 255}, font, renderer};
    b3.setOnClick([this]() {options();});

    buttons.push_back(std::move(b1));
    buttons.push_back(std::move(b2));
    buttons.push_back(std::move(b3));

    Button b4 = {(screenWidth / 2) - (buttonWidth / 2), 350, buttonWidth, buttonHeight, "Level 1", SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{0xFF, 0xFF, 0xFF, 255}, font, renderer};
    b4.setOnClick([this]() {startLevel1();});

    Button b5 = {(screenWidth / 2) - (buttonWidth / 2), 500, buttonWidth, buttonHeight, "Level 2", SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{0xFF, 0xFF, 0xFF, 255}, font, renderer};
    b5.setOnClick([this]() {startLevel2();});

    lvlButtons.push_back(std::move(b4));
    lvlButtons.push_back(std::move(b5));

}


void MenuState::loadTextures(){

    std::string pathBg = "textures/backgroundMenu.png";

    background = loadTextureM(renderer, pathBg.c_str());
}


void MenuState::startGame(){
    whatToDoNow = GameState::LEVEL1;
}

void MenuState::chooseLevel(){
    this->state = LEVELS;
}

void MenuState::options(){
    //this->state = OPTION;
}

void MenuState::startLevel1(){
    whatToDoNow = GameState::LEVEL1;
}

void MenuState::startLevel2(){
    whatToDoNow = GameState::LEVEL2;
}


MenuState::~MenuState(){
    //delete background;
    if (background != nullptr) {
        SDL_DestroyTexture(background);  
        background = nullptr;
    }
}


int MenuState::unload(){
    buttons.clear();

    if(Mix_PlayingMusic())
        Mix_HaltMusic();

    return 0;
}


GameState::StateCode MenuState::update(float /*dt*/){
    playBackgroundMusic();
    return whatToDoNow;
}


void MenuState::handleEvents(SDL_Event& events){

    if(state == WindowStat::NORMAL){
        for(Button& b : buttons){
            b.handleEvent(events);
        }
    }
    else if (state == WindowStat::LEVELS){
        for(Button& b : lvlButtons){
            b.handleEvent(events);
        }
    }
    
}


void MenuState::render(SDL_Renderer* renderer) {

    renderBackground(renderer);
    if(state == WindowStat::NORMAL){
        renderButtons();
    }
    else if (state == WindowStat::LEVELS){
        renderLevelButtons();
    }

    SDL_RenderPresent(renderer);
}


void MenuState::renderButtons(){
    for(Button& b : buttons){
        b.render();
    }
}

void MenuState::renderLevelButtons(){
    for(Button& b : lvlButtons){
        b.render();
    }
}


void MenuState::renderBackground(SDL_Renderer* renderer){

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect = {0, 0, 1400, 900};

    SDL_RenderCopy(renderer, background, NULL, &rect);
}


void MenuState::load_music(){
    music = Mix_LoadMUS("sounds_musics/Main Menu - The Legend of Zelda Collectors Edition.mp3");
    assert(music);
}
int MenuState::playBackgroundMusic() {
    if(!Mix_PlayingMusic()){
        Mix_VolumeMusic(20);
        if (Mix_PlayMusic(music, -1) == -1) { // -1 means loop infinitely
            std::cerr << "Erreur Mix_PlayMusic: " << Mix_GetError() << std::endl;
            Mix_FreeMusic(music);
            Mix_CloseAudio();
            SDL_Quit();
            return 1;
        }
        
    }


    return 0;
}

SDL_Texture* loadTextureM(SDL_Renderer* renderer, const char* path){
    SDL_Texture* texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", path);

    texture = IMG_LoadTexture(renderer, path);

    if (!texture) {
        std::cerr << "Failed to load texture: " << path << "\n";
        std::cerr << "Error: " << IMG_GetError() << "\n"; 
        exit(1);
    }

    return texture;
}