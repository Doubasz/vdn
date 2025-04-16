

#include "SDLJeu.h"
#include <string>


// TODO implement animation depending the state of the player

SDLJeu::SDLJeu() : moveTimer(0.3), attacksound(0.5){

    jeu = Jeu();
    gameState = MAIN_MENU;


    Player& player = jeu.getCurrentLevel().getPlayer();

    int windowFlags = 0;
    int rendererFlags = SDL_RENDERER_ACCELERATED;

    tileSize = 48;
    blinkInterval = 1;

    quit = false;

    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();
    
    int width = gameMap[0].size() * tileSize;
    int height = gameMap.size() * tileSize;

    camera = Camera(1400, 900, width, height);


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

    loadTextures();
    loadAnimations();
    assert(loadSounds(0) == 0) ;
    playBackgroundMusic(0,0);
    //later do the niv and the state in parametres to choose which music is playing

    displayMap(gameMap);



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
    SDL_DestroyTexture(tileSet);
}

void SDLJeu::loadTextures(){

    char* path = "textures/assets/Tiles/Assets/Assets2x.png";
    char* pathBg = "textures/assets/Tiles/Assets/background1.png";
    char* pathBg2 = "textures/assets/Tiles/Assets/background2.png";
    char* pathPlayer = "textures/assets/player/adventurer-Sheet.png";
    char* pathEnnemy = "textures/assets/ennemy/ennemySheet1.png";

    tileSet = loadTexture(renderer, path);
    background = loadTexture(renderer, pathBg);
    background1 = loadTexture(renderer, pathBg2);
    playerSheet = loadTexture(renderer, pathPlayer);
    ennemySheet = loadTexture(renderer, pathEnnemy);
}


void SDLJeu::loadAnimations(){

    int spriteWidth = 50;
    int spriteHeight = 37;
    
    int sheetWidth = 350;
    int sheetHeight = 407;

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
int SDLJeu::loadSounds(int niveau) {

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Erreur Mix_OpenAudio: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    music = Mix_LoadMUS("sounds_musics/Steam Gardens - Super Mario Odyssey OST(1).mp3");

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

int SDLJeu::playBackgroundMusic(int niveau, int state) {

    Mix_VolumeMusic(20);
    if (Mix_PlayMusic(music, -1) == -1) { // -1 means loop infinitely
        std::cerr << "Erreur Mix_PlayMusic: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }


    return 0;
}



bool jumping = false;



void SDLJeu::playSound(std::string input){
    bool falling;
    bool fell ;
    bool playerOnGround = jeu.getCurrentLevel().getPlayer().getOnGround();
    
    
    if(contains(input,'q') || contains(input,'d')){

        if(moveTimer.canProceed()){ 
            if(playerOnGround){

                Mix_VolumeChunk(walk,30);
                Mix_PlayChannel(-1,walk,0);
            }

            moveTimer.reset();

        }

    }else if (contains(input,' ')){
        if(!jumping && jeu.getCurrentLevel().getPlayer().getState() == JUMP){
            
            jumping = true;

            Mix_VolumeChunk(sauter, 20);
            Mix_PlayChannel(-1,sauter,0);
        }

    }else if (contains(input,'m')){
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




void SDLJeu::updateAnimation(float deltaTime){

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

    

    //setAnimation(stateAnim);

    
    /*switch(state){
        case IDLE:
    }*/
}

void SDLJeu::updateEnnemyAnimation(float deltaTime){

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


void SDLJeu::setAnimation(int playerAnim){
    /*nimation* newAnim = ;

    if(&currentAnim)*/
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

void SDLJeu::gameLoop(){

    const int FPS = 60;
    const int frameDelay = 1000 / FPS; 

    Uint32 frameStart;
    int frameTime;

    Uint32 lastTime = SDL_GetTicks();

    while(!quit){

        frameStart = SDL_GetTicks();

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        float effectiveDeltatime = 0;
        lastTime = currentTime;

        lastPlayerState = jeu.getCurrentLevel().getPlayer().getState();
        input(deltaTime);
        update(deltaTime);
        updateEnnemyAnimation(deltaTime);
        updateAnimation(deltaTime);
        draw();
        

            // Cap FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);  // Wait for next frame
        }
    }
}

void SDLJeu::update(float deltaTime){

    Rectangle playerRect = jeu.getCurrentLevel().getPlayer().getBox();
    bool gotHit = jeu.getCurrentLevel().getPlayer().getGotHit();

    if(gotHit){
        camera.shake(3.0, 1.0);

        jeu.getCurrentLevel().getPlayer().setGotHit(false);
    }

    float playerCenterX = (playerRect.x + (playerRect.w / 2)) * tileSize;
    float playerCenterY = (playerRect.y + (playerRect.h / 2)) * tileSize;

    camera.update(playerCenterX, playerCenterY, deltaTime);
    gameTime += deltaTime;
}



void SDLJeu::input(float deltaTime){

    Vec2 mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    std::string input;

    SDL_Event event;

    while(SDL_PollEvent(&event)){

        switch(event.type){
            case SDL_QUIT:
                quit = true;
                exit(0);
                break;

            case SDL_KEYDOWN:
                
                break;
            
            default:
                break;
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]){
        //Log::log("q pressed");
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
    
    jeu.handleInput(input, deltaTime);
    playSound(input);
}




void SDLJeu::draw(){

    bool playerVulnerable = jeu.getCurrentLevel().getPlayer().getCanGetHit();

    drawBackground();
    drawTiles();
    drawPlayer();
    drawEnnemy();
    drawLives();
    drawTimer();

    SDL_RenderPresent(renderer);
    
} 


void SDLJeu::drawPlayer(){

    bool isVisible = jeu.getCurrentLevel().getPlayer().getIsVisible();
    if(!isVisible) return;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    int direction = jeu.getCurrentLevel().getPlayer().getDirection();

    if(direction == LEFT){
        flip = SDL_FLIP_HORIZONTAL;
    }

    Rectangle playerRect = jeu.getCurrentLevel().getPlayer().getBox();
    Rectangle attackHB = jeu.getCurrentLevel().getPlayer().getAttackHitBox();

    SDL_Rect rect = {playerRect.x * tileSize - camera.x, playerRect.y * tileSize - camera.y, tileSize, tileSize};
    SDL_Rect atkHB = {attackHB.x * tileSize - camera.x, attackHB.y * tileSize - camera.y, attackHB.w * tileSize, attackHB.h * tileSize};
    

    int spriteWidth = 50;
    int spriteHeight = 37;

    int playerWidth = 200;
    int playerHeight = 125;

    int sheetWidth = 350;
    int sheetHeight = 407;

    int sprtPerCol = 407 / 37;
    int sprtPerRow = 350 / 50; 


    
    SDL_Rect srcRect = { ((currentAnimation.startFrame + currentAnimation.currentFrame) % sprtPerRow) * spriteWidth,
                         ((currentAnimation.startFrame + currentAnimation.currentFrame) / sprtPerRow) * spriteHeight,
                        spriteWidth, spriteHeight};



    SDL_Rect dstRect = { ((playerRect.x * tileSize) - (playerWidth - tileSize) / 2) - camera.x,
                         ((playerRect.y * tileSize) - (playerHeight - 3 - tileSize)) - camera.y,
                    playerWidth, playerHeight};

    /*int playerState = jeu.getCurrentLevel().getPlayerState();
    drawTexture(renderer, playerTexture[playerState], playerRect);*/

    

    SDL_RenderCopyEx(renderer, playerSheet, &srcRect, &dstRect, 0.0, nullptr, flip);

    //drawRect(renderer, rect, SDL_Color(0, 255, 0));
    //drawRect(renderer, atkHB, SDL_Color{255, 0, 0});
}








void SDLJeu::drawEnnemy(){
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
            
        SDL_Rect dstRect = {((eBox.x * tileSize) - (tileSize / 2)) - camera.x,
                            ((eBox.y * tileSize)) - 3 - camera.y,
                            ennemyWidth, ennemyHeight};


        SDL_RenderCopyEx(renderer, ennemySheet, &srcRect, &dstRect, 0.0, nullptr, flip);

        SDL_Rect rect = SDL_Rect{
            (int)(e.box.x * tileSize - camera.x),
            (int)(e.box.y * tileSize - camera.y),
            tileSize, tileSize
        };
        //drawRect(renderer,rect, SDL_Color{0,255,255});
    }
}

void SDLJeu::drawTiles(){
    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();

    if (gameMap.empty() || gameMap[0].empty()) {
        Log::error("SDLJeu::drawTiles tileMap empty");
        return;
    }

    SDL_Color color;

    SDL_Rect rect = SDL_Rect{0, 0, tileSize, tileSize};

    int tilesetTextureWidth = 800;
    int tilesetWidthInTiles = tilesetTextureWidth / 32;

    

    for(int i = 0; i < gameMap[0].size(); i++){
        
        for(int j = 0; j < gameMap.size(); j++){

            int tileID = gameMap[j][i];
            if(tileID == NONE || tileID == PLAYER) continue;

            int tileIndex = tileID;
            int srcX = (tileIndex % tilesetWidthInTiles) * 32;
            int srcY = (tileIndex / tilesetWidthInTiles) * 32;

            /*rect.x = (int)((i * tileSize) - camera.x);
            rect.y = (int)((j * tileSize) - camera.y);

            switch(gameMap[j][i]){
                case NONE:
                    color = SDL_Color{100, 100, 200};
                    break;
            }

            if(gameMap[j][i] != NONE && gameMap[j][i] != PLAYER){
                color = SDL_Color{200, 100, 0};
            }
            

            drawRect(renderer, rect, color);*/

            SDL_Rect srcRect = { srcX, srcY, 32, 32 };
            SDL_Rect dstRect = { i * tileSize - camera.x, j * tileSize - camera.y, tileSize, tileSize };

            SDL_RenderCopy(renderer, tileSet, &srcRect, &dstRect);
        }
    }
    
}


void SDLJeu::drawBackground(){

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();

    Rectangle playerRect = jeu.getCurrentLevel().getPlayer().getBox();

    

    int width = gameMap[0].size() * tileSize;
    int height = gameMap.size() * tileSize;

    float scrollSpeed = 0.2f;

    SDL_Rect destRect = {-camera.x * 0.1, 0, width, height};
    SDL_Rect rectBg = {-camera.x * scrollSpeed, 0, width, height};

    

    //int textureWidth, textureHeight;
    //SDL_QueryTexture(background, NULL, NULL, &textureWidth, &textureHeight);
    SDL_RenderCopy(renderer, background1, NULL, &destRect);
    SDL_RenderCopy(renderer, background, NULL, &rectBg);

    

}


void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& rect){

    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}


SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path){
    SDL_Texture* texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", path);
    //Log::log("Loading " + std::string(path));

    texture = IMG_LoadTexture(renderer, path);

    if (!texture) {
        std::cerr << "Failed to load texture: " << path << "\n";
        std::cerr << "Error: " << IMG_GetError() << "\n"; // More accurate than SDL_GetError() for images
        exit(1);
    }

    return texture;
}

void SDLJeu::loadPlayerTextures(){

    //playerTexture.push_back(loadTexture(renderer, "textures/player.png"));
    //playerTexture.push_back(loadTexture(renderer, "textures/pebble.png"));
}   

void SDLJeu::loadPlatformTextures(){

    //platformTexture.push_back(loadTexture(renderer, "textures/platform.png"));
}

void drawRect(SDL_Renderer*& renderer, SDL_Rect& rect, SDL_Color color){

    SDL_SetRenderDrawColor(renderer, color.b, color.g, color.r, 255);
    SDL_RenderFillRect(renderer,  &rect);
    
}
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
    
    std::string timerText = "3 secondes";
    
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
                    gameState = LEVEL;  // On passe à l'état de jeu
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




