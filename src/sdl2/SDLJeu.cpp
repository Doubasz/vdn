

#include "SDLJeu.h"
#include <string>


// TODO implement animation depending the state of the player

SDLJeu::SDLJeu() {

    jeu = Jeu();
    //gameState = MAIN_MENU;


    Player& player = jeu.getCurrentLevel().getPlayer();

    

    int windowFlags = 0;
    int rendererFlags = SDL_RENDERER_ACCELERATED;



    quit = false;

    gameTime = 300; //300 seconds to finish the level or 5 min if u want
    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();
    
    


    font = nullptr;
    textColor = {255, 255, 255, 255}; // Couleur blanche
    

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        Log::error("SDLJeu::SDLJeu() Couldn't init SDL");
        Log::error(std::string (SDL_GetError()));
        exit(1);
    }

    if (TTF_Init() == -1) {
        Log::error("SDLJeu::SDLJeu() Couldn't init TTF" );
        Log::error(std::string (TTF_GetError()));
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

    


    //playBackgroundMusic(0,0);
    //later do the niv and the state in parametres to choose which music is playing

    displayMap(gameMap);

    currentState = std::make_unique<MenuState>(renderer, font);
    static_cast<MenuState*>(currentState.get())->load();
    

    GameState::StateCode lastState = GameState::MAIN_MENU;
    GameState::StateCode currentStateCode = GameState::MAIN_MENU;



    /*loadPlayerTextures();
    loadPlatformTextures();
*/
    //textures = loadAllTexture(renderer);

    /*TTF_Font* fontInit = TTF_OpenFont("/usr/share/fonts/truetype/Gargi/Gargi.ttf", 64);
    if (!fontInit) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(-1);
    }*/


}




SDLJeu::~SDLJeu(){
}

void SDLJeu::resetGame() {
    jeu = Jeu();  
    gameTime = 300;
}








/*void displayMap(const std::vector<std::vector<int>>& vec){

    std::cout << "GameMap" << std::endl;
    for (const auto& row : vec) {
        for (int tile : row) {
            std::cout << tile << " ";
        }
        std::cout << std::endl;
    }
}*/

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
        float effectiveDeltatime = 0;
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

            this->currentState->handleEvents(event, deltaTime);
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



GameState* SDLJeu::loadState(GameState::StateCode state){
    currentState->unload();
    
    switch (state) {
        case GameState::StateCode::MAIN_MENU:
            
            currentState = std::make_unique<MenuState>(renderer, font);
            static_cast<MenuState*>(currentState.get())->load();
            break;
        case GameState::StateCode::LEVEL:
            currentState = std::make_unique<InGameState>(renderer, DESERT);
            static_cast<InGameState*>(currentState.get())->load();
            break;
    }


}


/*void SDLJeu::renderMainMenu(){

    //drawBackground();

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    renderButtons();

    
    //SDL_RenderButtons();


    SDL_RenderPresent(renderer);
}*/





    /*if (gameState == GAME_PAUSED && font) {
        
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);  
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);              
        SDL_Rect darkOverlay = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderFillRect(renderer, &darkOverlay);
    
        
        SDL_Color black = {0, 0, 0, 255};
        SDL_Surface* pauseSurface = TTF_RenderText_Solid(font, "PAUSE", black);
        SDL_Texture* pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);
        SDL_Rect pauseRect = {
            SCREEN_WIDTH / 2 - pauseSurface->w / 2,
            20,
            pauseSurface->w,
            pauseSurface->h
        };
        SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
    
        SDL_FreeSurface(pauseSurface);
        SDL_DestroyTexture(pauseTexture);



        SDL_SetRenderDrawColor(renderer, 200, 30, 30, 255);  // rouge vif
        SDL_RenderFillRect(renderer, &quitButtonRect);

        SDL_Surface* quitSurface = TTF_RenderText_Solid(font, "Quitter", textColor);
        SDL_Texture* quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);
        SDL_Rect quitTextRect = {
        quitButtonRect.x + (quitButtonRect.w - quitSurface->w) / 2,
        quitButtonRect.y + (quitButtonRect.h - quitSurface->h) / 2,
        quitSurface->w,
        quitSurface->h
};
        SDL_RenderCopy(renderer, quitTexture, NULL, &quitTextRect);
        SDL_FreeSurface(quitSurface);
        SDL_DestroyTexture(quitTexture);
    
        
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }
    
    
    */


void SDLJeu::loadFont() {
    font = TTF_OpenFont("textures/fonts/yakuza.ttf", 24); 
    if (!font) {
        Log::error("Failed to load font: " + std::string(TTF_GetError()));
    }
}

void SDLJeu::drawLives() {
    if (!font) return; 
    
    int lives = jeu.getCurrentLevel().getPlayer().getHp();
    std::string livesText = "Lives: " + std::to_string(lives);
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, livesText.c_str(), textColor);
    if (!surface) {
        Log::error("Unable to render text: " + std::string(TTF_GetError()));
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        Log::error("Unable to create texture from text: " + std::string(SDL_GetError()));
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect destRect = {20, 20, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


void SDLJeu::drawTimer() {
    if (!font) return; // Si la police n'est pas chargée
    
    // Convertir le temps en minutes:secondes
    int minutes = static_cast<int>(gameTime) / 60;
    int seconds = static_cast<int>(gameTime) % 60;
    
    std::string timerText = std::to_string(minutes) + ":" + std::to_string(seconds);
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, timerText.c_str(), textColor);
    if (!surface) {
        Log::error("Unable to render timer text: " + std::string(TTF_GetError()));
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        Log::error("Unable to create texture from timer text: " + std::string(SDL_GetError()));
        SDL_FreeSurface(surface);
        return;
    }
    
    // Position en haut à droite (SCREEN_WIDTH - largeur_texte - marge)
    SDL_Rect destRect = {SCREEN_WIDTH - surface->w - 20, 20, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void SDLJeu::renderMainMenu() {
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

        // Bouton "Start"
        SDL_Rect startButton = {600, 400, 200, 70};
        SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255); // bleu clair
        SDL_RenderFillRect(renderer, &startButton);

        SDL_Surface* startText = TTF_RenderText_Solid(font, "Start", white);
        SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startText);
        SDL_Rect startTextRect = {startButton.x + 50, startButton.y + 20, startText->w, startText->h};
        SDL_RenderCopy(renderer, startTexture, NULL, &startTextRect);
        SDL_FreeSurface(startText);
        SDL_DestroyTexture(startTexture);

        SDL_RenderPresent(renderer);
    }
}






