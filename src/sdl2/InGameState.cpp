
#include "InGameState.h"


InGameState::InGameState(){

    tileSize = 48;
    blinkInterval = 1;
    state = CONTINUE;

    this->renderer = nullptr;
}


InGameState::InGameState(SDL_Renderer* renderer, int lvl) : InGameState(){
    this->renderer = renderer;
    this->level = lvl;
}


void InGameState::load(){

    if(!renderer){
        std::cout << "InGameState::load : render is nullptr" << std::endl;
        exit(-1);
    }

    tileSize = 48;
    blinkInterval = 1;

    jeu.loadLevel(level);

    loadTextures(renderer);
    loadAnimations();

    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();
    
    int width = gameMap[0].size() * tileSize;
    int height = gameMap.size() * tileSize;

    camera = Camera(1400, 900, width, height);

}



void InGameState::loadAnimations(){

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


void InGameState::loadTextures(SDL_Renderer* renderer){

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

int InGameState::unload(){

}

void InGameState::handleEvents(SDL_Event& events, float deltaTime){

    switch(events.type){
        case SDL_KEYDOWN:
            if (events.key.keysym.sym == SDLK_ESCAPE){
                state = QUIT;
            }
    }

    
    
}

GameState::StateCode InGameState::update(float dt){

    lastPlayerState = jeu.getCurrentLevel().getPlayer().getState();

    updateGame(dt);
    updateCamera(dt);
    updateEnnemyAnimation(dt);
    updateAnimation(dt);
    


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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 125);
        SDL_RenderClear(renderer);
    }

    SDL_RenderPresent(renderer);
    
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


void InGameState::renderTiles(SDL_Renderer* renderer){
    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();

    if (gameMap.empty() || gameMap[0].empty()) {
        std::cout << "InGameState::renderTiles tileMap empty" << std::endl;
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



void InGameState::renderBackground(SDL_Renderer* renderer){
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
void InGameState::renderLives(SDL_Renderer* renderer){

}   
void InGameState::renderTimer(SDL_Renderer* renderer){

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

    

    //setAnimation(stateAnim);

    
    /*switch(state){
        case IDLE:
    }*/
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
