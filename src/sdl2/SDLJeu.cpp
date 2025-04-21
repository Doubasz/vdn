

#include "SDLJeu.h"
#include <string>


SDLJeu::SDLJeu() {

    int windowFlags = 0;
    int rendererFlags = SDL_RENDERER_ACCELERATED;

    quit = false;
    
    font = nullptr;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDLJeu::SDLJeu() Couldn't init SDL" << std::endl;
        std::cout << std::string (SDL_GetError()) << std::endl;
        exit(1);
    }

    if (TTF_Init() == -1) {
        std::cout << "SDLJeu::SDLJeu() Couldn't init TTF" << std::endl;
        std::cout << std::string (TTF_GetError()) << std::endl;
        exit(1);
    }

    loadFont();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer Error: " << Mix_GetError() << std::endl;
        exit(1);
    }
    

    window = SDL_CreateWindow("Vent du Nord", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);


    currentState = std::make_unique<MenuState>(renderer, font);
    static_cast<MenuState*>(currentState.get())->load();
    
    lastState = GameState::StateCode::MAIN_MENU;
    currentStateCode = GameState::StateCode::MAIN_MENU;
}


SDLJeu::~SDLJeu(){
}


void SDLJeu::run(){
    const int FPS = 60;
    const int frameDelay = 1000 / FPS; 

    Uint32 frameStart;
    int frameTime;

    Uint32 lastTime = SDL_GetTicks();

    SDL_Event event;

    while(!quit){
        frameStart = SDL_GetTicks();

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        lastState = currentStateCode;


        while(SDL_PollEvent(&event)){

            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    exit(0);
                    break;
                
                default:
                    break;
            }

            this->currentState->handleEvents(event);
        }

        currentStateCode = this->currentState->update(deltaTime);
        this->currentState->render(renderer);

        
    
        if(currentStateCode != lastState){
            loadState(currentStateCode);
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);  // Wait for next frame
        }
    }

}



void SDLJeu::loadState(GameState::StateCode state){
    currentState->unload();

    switch (state) {
        case GameState::StateCode::MAIN_MENU:
            
            currentState = std::make_unique<MenuState>(renderer, font);
            static_cast<MenuState*>(currentState.get())->load();
            break;
        case GameState::StateCode::LEVEL:
            currentState = std::make_unique<InGameState>(renderer, font ,DESERT);
            static_cast<InGameState*>(currentState.get())->load();
            break;
        default:
            break;
    }
}


void SDLJeu::loadFont() {
    font = TTF_OpenFont("textures/fonts/yakuza.ttf", 24); 
    if (!font) {
        std::cout << "Failed to load font: " + std::string(TTF_GetError()) << std::endl;
        exit(-1);
    }
}