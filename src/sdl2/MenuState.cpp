


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

    loadTextures();
    initButtons();

    whatToDoNow = GameState::MAIN_MENU;

    load_music();

}


void MenuState::initButtons(){

    int screenWidth = 1400;
    int screenHeight = 900;

    int buttonWidth = 400;
    int buttonHeight = 100;

    Button b1 = {(screenWidth / 2) - (buttonWidth / 2), 350, buttonWidth, buttonHeight, "Start game", SDL_Color{0, 0, 0, 255}, SDL_Color{200, 100, 20, 255}, SDL_Color{50, 100, 50, 255}, SDL_Color{0xFF, 0xFF, 0, 255}, font, renderer};
    // [this]() { runPerft(); };
    b1.setOnClick([this]() {startGame();});

    Button b2 = {(screenWidth / 2) - (buttonWidth / 2), 500, buttonWidth, buttonHeight, "Options", SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{0xFF, 0xFF, 0xFF, 255}, font, renderer};
    
    buttons.push_back(std::move(b1));
    buttons.push_back(std::move(b2));

}


void MenuState::loadTextures(){

    std::string pathBg = "textures/backgroundMenu.png";

    background = loadTexture(renderer, pathBg.c_str());
}





void MenuState::startGame(){
    whatToDoNow = GameState::LEVEL;
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
}


GameState::StateCode MenuState::update(float dt){
    playBackgroundMusic();
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


/*void renderMainMenu() {
    SDL_Event event;
    bool inMenu = true;

    SDL_Color white = {255, 255, 255, 255};

    while (inMenu) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                inMenu = false;
                quit = true;
                return;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // Bouton "Start"
                if (x >= 600 && x <= 800 && y >= 400 && y <= 470) {
                    inMenu = false;
                    //gameState = LEVEL;  // On passe à l'état de jeu
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
        SDL_RenderClear(renderer);

        // Titre
        SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "Vent du Nord", white);
        SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
        SDL_Rect titleRect = {SCREEN_WIDTH / 2 - titleSurface->w / 2, 200, titleSurface->w, titleSurface->h};
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
        SDL_FreeSurface(titleSurface);
        SDL_DestroyTexture(titleTexture);

        
        
        SDL_Surface* startText = TTF_RenderText_Solid(font, "Start", white);
        SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startText);
        SDL_Rect startTextRect = {startButton.x + 50, startButton.y + 20, startText->w, startText->h};
        SDL_RenderCopy(renderer, startTexture, NULL, &startTextRect);
        SDL_FreeSurface(startText);
        SDL_DestroyTexture(startTexture);

        SDL_RenderPresent(renderer);
    }
}*/


SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path){
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
