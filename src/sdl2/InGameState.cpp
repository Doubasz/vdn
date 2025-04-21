
#include "InGameState.h"


InGameState::InGameState(): moveTimer(0.3), attacksound(0.5){

    tileSize = 48;
    blinkInterval = 1;
    state = CONTINUE;

    this->renderer = nullptr;
}


InGameState::InGameState(SDL_Renderer* renderer, TTF_Font* font, int lvl) : InGameState(){
    this->renderer = renderer;
    this->level = lvl;
    this->font = font;
}


void InGameState::load(){

    if(!renderer){
        std::cout << "InGameState::load : render is nullptr" << std::endl;
        exit(-1);
    }
    if(!font){
        std::cout << "InGameState::load : font is nullptr" << std::endl;
        exit(-1);
    }


    tileSize = 48;
    blinkInterval = 1;

    jeu.loadLevel(level);

    loadTextures(renderer);
    loadAnimations();
    loadSounds(0);
    initButtons();

    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();
    
    int width = gameMap[0].size() * tileSize;
    int height = gameMap.size() * tileSize;

    camera = Camera(1400, 900, width, height);

}


SDL_Texture* InGameState::getTileSet() const {
    return tileSet;
}

SDL_Texture* InGameState::getBackground() const {
    return background;
}
SDL_Texture* InGameState::getPlayerSheet() const {
    return playerSheet;
}

SDL_Texture* InGameState::getEnnemySheet() const {
    return ennemySheet;
}

SDL_Texture* InGameState::getBackground1() const {
    return background1;
}
const std::vector<Animation>& InGameState::getPlayerAnimation() const {
    return playerAnimation;
}
void InGameState::loadAnimations(){

    //spriteWidth = 50;
    //spriteHeight = 37;
    
    //sheetWidth = 350;
    //sheetHeight = 407;

    Animation idleAnim = {0, 4, 0, 0.3f, 0.0, true};
    Animation runAnim = {8, 6, 0, 0.1f, 0.0, true};
    Animation jumpAnim = {14, 8, 0, 0.07f, 0.0, false};
    Animation fallAnim = {22, 2, 0, 0.07f, 0.0, true};
    Animation atkAnim = {54, 7, 0, 0.08f, 0.0, false};
    
    playerAnimation.push_back(idleAnim);
    playerAnimation.push_back(runAnim);
    playerAnimation.push_back(jumpAnim);
    playerAnimation.push_back(fallAnim);
    playerAnimation.push_back(atkAnim);

    currentAnimation = playerAnimation[IDLE];

    Animation ennemyRunning = {3, 8, 0, 0.4f, 0.0, true};
    ennemyAnimation = ennemyRunning;

}


void InGameState::loadTextures(SDL_Renderer* renderer){

    const char* path = "textures/assets/Tiles/Assets/Assets2x.png";
    const char* pathBg = "textures/assets/Tiles/Assets/background1.png";
    const char* pathBg2 = "textures/assets/Tiles/Assets/background2.png";
    const char* pathPlayer = "textures/assets/player/adventurer-Sheet.png";
    const char* pathEnnemy = "textures/assets/ennemy/ennemySheet1.png";

    tileSet = loadTexture(renderer, path);
    background = loadTexture(renderer, pathBg);
    background1 = loadTexture(renderer, pathBg2);
    playerSheet = loadTexture(renderer, pathPlayer);
    ennemySheet = loadTexture(renderer, pathEnnemy);
}


void InGameState::initButtons(){

    int screenWidth = 1400;
    //screenHeight = 900;

    int buttonWidth = 400;
    int buttonHeight = 100;

    Button b1 = {(screenWidth / 2) - (buttonWidth / 2), 350, buttonWidth, buttonHeight, "Resume", SDL_Color{0, 0, 0, 255}, SDL_Color{200, 100, 20, 255}, SDL_Color{50, 100, 50, 255}, SDL_Color{0xFF, 0xFF, 0, 255}, font, renderer};
    b1.setOnClick([this]() {resumeGame();});

    Button b2 = {(screenWidth / 2) - (buttonWidth / 2), 500, buttonWidth, buttonHeight, "Quit", SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{100, 100, 255, 255}, SDL_Color{0xFF, 0xFF, 0xFF, 255}, font, renderer};
    b2.setOnClick([this]() {quitGame();});

    buttons.push_back(std::move(b1));
    buttons.push_back(std::move(b2));

}


void InGameState::resumeGame(){
    this->state = CONTINUE;
}

void InGameState::quitGame(){
    this->state = QUIT;
}


int InGameState::unload(){

    platformTexture.clear();
    playerAnimation.clear();
    buttons.clear();
    
    if(Mix_PlayingMusic()){
        Mix_HaltMusic();
    }
    return 0;
}

void InGameState::handleEvents(SDL_Event& events){

    switch(events.type){
        case SDL_KEYDOWN:
            if (events.key.keysym.sym == SDLK_ESCAPE){
                state = (state == WindowState::PAUSE) ? WindowState::CONTINUE : WindowState::PAUSE; 
            }
    }

    for(Button& b : buttons){
        b.handleEvent(events);
    }
}

GameState::StateCode InGameState::update(float dt){

    lastPlayerState = jeu.getCurrentLevel().getPlayer().getState();
    playBackgroundMusic();
    if(state != PAUSE){
        updateGame(dt);
        updateCamera(dt);
        updateEnnemyAnimation(dt);
        updateAnimation(dt);
    }


    if(state == QUIT){
        return GameState::MAIN_MENU;
    }
    return GameState::LEVEL;
}



void InGameState::updateGame(float deltaTime){

    std::string input = "";

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]){
        input += "q";
    }
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]){
        input += "d";
    }
    if (keys[SDL_SCANCODE_M]){
        input += "m";
    }
    if(keys[SDL_SCANCODE_SPACE]){
        input += " ";
    }

    if(state != PAUSE){
        jeu.update(input, deltaTime);
        playSound(input);
    }
}


void InGameState::updateCamera(float dt){
    Rectangle playerRect = jeu.getCurrentLevel().getPlayer().getBox();
    bool gotHit = jeu.getCurrentLevel().getPlayer().getGotHit();

    if(gotHit){
        camera.shake(3.0, 1.0);

        jeu.getCurrentLevel().getPlayer().setGotHit(false);
    }

    float playerCenterX = (playerRect.x + (playerRect.w / 2)) * tileSize;
    float playerCenterY = (playerRect.y + (playerRect.h / 2)) * tileSize;

    camera.update(playerCenterX, playerCenterY, dt);
}


void InGameState::render(SDL_Renderer* renderer){

    renderBackground(renderer);
    renderTiles(renderer);
    renderPlayer(renderer);
    renderEnnemy(renderer);
    renderLives(renderer);
    renderTimer(renderer);

    if(state == PAUSE){
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);              
        SDL_Rect darkOverlay = {0, 0, 1400, 900};
        SDL_RenderFillRect(renderer, &darkOverlay);

        renderButtons();
    }

    SDL_RenderPresent(renderer);
    
}


void InGameState::renderButtons(){
    for(Button& b : buttons){
        b.render();
    }
}

void InGameState::renderPlayer(SDL_Renderer* renderer){
    bool isVisible = jeu.getCurrentLevel().getPlayer().getIsVisible();
    if(!isVisible) return;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    int direction = jeu.getCurrentLevel().getPlayer().getDirection();

    if(direction == LEFT){
        flip = SDL_FLIP_HORIZONTAL;
    }

    Rectangle playerRect = jeu.getCurrentLevel().getPlayer().getBox();

    int spriteWidth = 50;
    int spriteHeight = 37;

    int playerWidth = 200;
    int playerHeight = 125;

    int sprtPerRow = 350 / 50; 


    
    SDL_Rect srcRect = { ((currentAnimation.startFrame + currentAnimation.currentFrame) % sprtPerRow) * spriteWidth,
                         ((currentAnimation.startFrame + currentAnimation.currentFrame) / sprtPerRow) * spriteHeight,
                        spriteWidth, spriteHeight};



    SDL_Rect dstRect = {
        static_cast<int>((playerRect.x * tileSize) - (playerWidth - tileSize) / 2 - camera.x),
        static_cast<int>((playerRect.y * tileSize) - (playerHeight - 3 - tileSize) - camera.y),
        playerWidth,
        playerHeight
    };

    SDL_RenderCopyEx(renderer, playerSheet, &srcRect, &dstRect, 0.0, nullptr, flip);
}  


void InGameState::renderEnnemy(SDL_Renderer* renderer){
    std::vector<Ennemy> ennemies = jeu.getCurrentLevel().getEnnemies();

    for (Ennemy& e : ennemies){

        int direction = e.getDirection();
        SDL_RendererFlip flip = (direction == RIGHT) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        Rectangle eBox = e.getBox();

        int spriteWidth = 64;
        int spriteHeight = 64;

        int ennemyWidth = 100;
        int ennemyHeight = 64;

        int sprtPerRow = 1090 / 64;

        SDL_Rect srcRect = {((ennemyAnimation.startFrame + ennemyAnimation.currentFrame) % sprtPerRow) * spriteWidth,
                            ((ennemyAnimation.startFrame + ennemyAnimation.currentFrame) / sprtPerRow) * spriteHeight,
                            spriteWidth, spriteHeight};
            
        SDL_Rect dstRect = {
            static_cast<int>((eBox.x * tileSize) - (tileSize / 2) - camera.x),
            static_cast<int>((eBox.y * tileSize) - 3 - camera.y),
            ennemyWidth,
            ennemyHeight
        };
                            


        SDL_RenderCopyEx(renderer, ennemySheet, &srcRect, &dstRect, 0.0, nullptr, flip);
    }
}


void InGameState::renderTiles(SDL_Renderer* renderer){
    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();

    if (gameMap.empty() || gameMap[0].empty()) {
        std::cout << "InGameState::renderTiles tileMap empty" << std::endl;
        return;
    }

    int tilesetTextureWidth = 800;
    int tilesetWidthInTiles = tilesetTextureWidth / 32;

    for(size_t i = 0; i < gameMap[0].size(); i++){
        
        for(size_t j = 0; j < gameMap.size(); j++){

            int tileID = gameMap[j][i];
            if(tileID == NONE || tileID == PLAYER) continue;

            int tileIndex = tileID;
            int srcX = (tileIndex % tilesetWidthInTiles) * 32;
            int srcY = (tileIndex / tilesetWidthInTiles) * 32;

            SDL_Rect srcRect = { srcX, srcY, 32, 32 };
            SDL_Rect dstRect = { 
                static_cast<int>(i * tileSize - camera.x),
                static_cast<int> (j * tileSize - camera.y),
                tileSize, tileSize };

            SDL_RenderCopy(renderer, tileSet, &srcRect, &dstRect);
        }
    }
}



void InGameState::renderBackground(SDL_Renderer* renderer){

    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();

    int width = gameMap[0].size() * tileSize;
    int height = gameMap.size() * tileSize;

    float scrollSpeed = 0.2f;

    SDL_Rect destRect = {static_cast<int>(-camera.x * 0.1f), 0, width, height};
    SDL_Rect rectBg = {static_cast<int>(-camera.x * scrollSpeed), 0, width, height};

    SDL_RenderCopy(renderer, background1, NULL, &destRect);
    SDL_RenderCopy(renderer, background, NULL, &rectBg);
}



void InGameState::renderLives(SDL_Renderer* renderer){
    if (!font) return; 
    
    int lives = jeu.getCurrentLevel().getPlayer().getHp();
    std::string livesText = "Lives: " + std::to_string(lives);
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, livesText.c_str(), textColor);
    if (!surface) {
        std::cout << "Unable to render text: " + std::string(TTF_GetError()) << std::endl;
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cout << "Unable to create texture from text: " + std::string(SDL_GetError()) << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect destRect = {20, 20, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}   




void InGameState::renderTimer(SDL_Renderer* renderer){
    if (!font) return; 
    
    // Convertir le temps en minutes:secondes
    int minutes = static_cast<int>(gameTime) / 60;
    int seconds = static_cast<int>(gameTime) % 60;
    
    std::string timerText = std::to_string(minutes) + ":" + std::to_string(seconds);
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, timerText.c_str(), textColor);
    if (!surface) {
        std::cout << "Unable to render timer text: " + std::string(TTF_GetError()) << std::endl;
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cout << "Unable to create texture from timer text: " + std::string(SDL_GetError()) << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    
    // Position en haut à droite (SCREEN_WIDTH - largeur_texte - marge)
    SDL_Rect destRect = {SCREEN_WIDTH - surface->w - 20, 20, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}







void InGameState::updateAnimation(float deltaTime){

    currentAnimation.timer += deltaTime;

    if(currentAnimation.timer >= currentAnimation.frameTime){
        currentAnimation.timer = 0;
        currentAnimation.currentFrame++;

        if(currentAnimation.currentFrame >= currentAnimation.numFrames){
            if(currentAnimation.loop){
                currentAnimation.currentFrame = 0;
            }
            else{
                currentAnimation.currentFrame = currentAnimation.numFrames - 1;
            }
        }
    }

    int stateAnim = jeu.getCurrentLevel().getPlayer().getState();

    if(lastPlayerState != stateAnim){
        currentAnimation = playerAnimation[stateAnim];
    }
}

void InGameState::updateEnnemyAnimation(float deltaTime){

    ennemyAnimation.timer += deltaTime;

    if(ennemyAnimation.timer >= ennemyAnimation.frameTime){
        ennemyAnimation.timer = 0;
        ennemyAnimation.currentFrame++;

        if(ennemyAnimation.currentFrame >= ennemyAnimation.numFrames){
            if(ennemyAnimation.loop){
                ennemyAnimation.currentFrame = 0;
            }
            else{
                ennemyAnimation.currentFrame = ennemyAnimation.numFrames - 1;
            }
        }
    }
}

int InGameState::loadSounds(int niveau) {

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Erreur Mix_OpenAudio: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    music = Mix_LoadMUS("sounds_musics/Steam Gardens - Super Mario Odyssey OST(1).mp3");
    //music = Mix_LoadMUS("sounds_musics/peak1.mp3");


    if (!music) {
        std::cerr << "Erreur Mix_LoadMUS: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    walk = Mix_LoadWAV("sounds_musics/walkgrass.mp3");

    if (!walk) {
        std::cerr << "Erreur Mix_LoadWAV: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    sauter = Mix_LoadWAV("sounds_musics/jump.mp3");

    if (!sauter) {
        std::cerr << "Erreur Mix_LoadWAV: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    land = Mix_LoadWAV("sounds_musics/land.wav");
    if (!land) {
        std::cerr << "Erreur Mix_LoadWAV: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }


    attack = Mix_LoadWAV("sounds_musics/attack.mp3");
    //attack = Mix_LoadWAV("sounds_musics/oraora.mp3");

    if (!attack) {
        std::cerr << "Erreur Mix_LoadWAV: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }
    gotHit = Mix_LoadWAV("sounds_musics/gotHit.wav");
    if (!gotHit) {
        std::cerr << "Erreur Mix_LoadWAV: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    return 0;
}

int InGameState::playBackgroundMusic() {

    if(state == PAUSE){
        Mix_VolumeMusic(8);
    }else{
        Mix_VolumeMusic(20);
    }

    if(!Mix_PlayingMusic()){
        
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




bool jumping = false;



void InGameState::playSound(std::string input){
    bool falling;
    bool playerOnGround = jeu.getCurrentLevel().getPlayer().getOnGround();
    
    
    if(contains(input,'q') || contains(input,'d')){

        if(moveTimer.canProceed()){ 
            if(playerOnGround){

                Mix_VolumeChunk(walk,30);
                Mix_PlayChannel(-1,walk,0);
            }

            moveTimer.reset();

        }

    } if (contains(input,' ')){
        if(!jumping && jeu.getCurrentLevel().getPlayer().getState() == JUMP){
            
            jumping = true;

            Mix_VolumeChunk(sauter, 20);
            Mix_PlayChannel(-1,sauter,0);
        }

    } if (contains(input,'m')){
        if(attacksound.canProceed()){
            Mix_VolumeChunk(attack, 90);
            Mix_PlayChannel(-1,attack,0);
            attacksound.reset();

        }
    }
    if(playerOnGround)
        jumping = false;
    if(jeu.getCurrentLevel().getPlayer().getState() == FALLING )  {
        falling = true;
    }
    if(falling && playerOnGround){
        Mix_VolumeChunk(land, 20);
        Mix_PlayChannel(-1,land,0);
    }

    if(jeu.getCurrentLevel().getPlayer().getGotHit()){
    
        Mix_VolumeChunk(gotHit, 128);
        Mix_PlayChannel(-1,gotHit,0);
    }
}


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