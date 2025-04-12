

#include "SDLJeu.h"
#include <string>

// TODO implement animation depending the state of the player

SDLJeu::SDLJeu(){

    jeu = Jeu();

    Player& player = jeu.getCurrentLevel().getPlayer();

    int windowFlags = 0;
    int rendererFlags = SDL_RENDERER_ACCELERATED;

    tileSize = 48;

    quit = false;

    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();
    
    int width = gameMap[0].size() * tileSize;
    int height = gameMap.size() * tileSize;

    camera = Camera(1400, 900, width, height);


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

    window = SDL_CreateWindow("Vent du Nord", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);


    loadTextures();
    loadAnimations();

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

    tileSet = loadTexture(renderer, path);
    background = loadTexture(renderer, pathBg);
    background1 = loadTexture(renderer, pathBg2);
    playerSheet = loadTexture(renderer, pathPlayer);
}


void SDLJeu::loadAnimations(){

    int spriteWidth = 50;
    int spriteHeight = 37;
    
    int sheetWidth = 350;
    int sheetHeight = 407;

    Animation idleAnim = {0, 4, 0, 0.3f, 0.0, true};
    Animation runAnim = {8, 6, 0, 0.1f, 0.0, true};
    Animation jumpAnim = {14, 10, 0, 0.07f, 0.0, false};
    
    playerAnimation.push_back(idleAnim);
    playerAnimation.push_back(runAnim);
    playerAnimation.push_back(jumpAnim);

    currentAnimation = playerAnimation[IDLE];

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


void SDLJeu::scale(){


    Player &player = jeu.getCurrentLevel().getPlayer();

    player.getBox().setX(player.getBox().x * 32);
    player.getBox().setY(player.getBox().y * 32);
    player.setDim(player.getDim().x * 32, player.getDim().y * 32);


    std::vector<Platform>& platforms = jeu.getCurrentLevel().getPlatforms();

    for (Platform& p : platforms){

        p.getBox().setX(p.getBox().x * 32);
        p.getBox().setY(p.getBox().y * 32);
    
        p.setDim(p.getDim().x * 32, p.getDim().y * 32);
    }


}

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
        lastTime = currentTime;

        lastPlayerState = jeu.getCurrentLevel().getPlayer().getState();
        input(deltaTime);
        update();
        updateAnimation(deltaTime);
        draw();
        

            // Cap FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);  // Wait for next frame
        }
    }
}

void SDLJeu::update(){

    Rectangle playerRect = jeu.getCurrentLevel().getPlayer().getBox();

    float playerCenterX = (playerRect.x + (playerRect.w / 2)) * tileSize;
    float playerCenterY = (playerRect.y + (playerRect.h / 2)) * tileSize;

    camera.update(playerCenterX, playerCenterY);
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
    if(keys[SDL_SCANCODE_SPACE]){
        input += " ";
    }
    jeu.handleInput(input, deltaTime);
}




void SDLJeu::draw(){

    drawBackground();
    drawTiles();
    drawPlayer();
    drawEnnemy();
    

    SDL_RenderPresent(renderer);
}



void SDLJeu::cameraUpdate(){
    Rectangle playerRect = jeu.getCurrentLevel().getPlayer().getBox();
    std::vector<std::vector<int>> gameMap = jeu.getCurrentLevel().getGameMap();

    camera.x = (playerRect.x + (playerRect.w / 2)) - (camera.w / 2);
    camera.y = (playerRect.y + (playerRect.h / 2)) - (camera.h / 2);

    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;

    int width = gameMap[0].size() * tileSize;
    int height = gameMap.size() * tileSize;

    if(camera.x > width - camera.w) camera.x = width - camera.w;
    if(camera.y > height - camera.h) camera.y = height - camera.h;
}


void SDLJeu::drawPlayer(){

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    int direction = jeu.getCurrentLevel().getPlayer().getDirection();

    if(direction == LEFT){
        flip = SDL_FLIP_HORIZONTAL;
    }

    Rectangle playerRect = jeu.getCurrentLevel().getPlayer().getBox();

    SDL_Rect rect = {playerRect.x * tileSize - camera.x, playerRect.y * tileSize - camera.y, tileSize, tileSize};
    

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

    //drawRect(renderer, rect, SDL_Color{0, 255, 0});
}

void SDLJeu::drawEnnemy(){
    std::vector<Ennemy> ennemies = jeu.getCurrentLevel().getEnnemies();

    for (Ennemy& e : ennemies){
        SDL_Rect rect = SDL_Rect{
            (int)(e.box.x * tileSize - camera.x),
            (int)(e.box.y * tileSize - camera.y),
            tileSize, tileSize
        };
        drawRect(renderer,rect, SDL_Color{0,255,255});
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
    SDL_RenderFillRect(renderer, &rect);
    
}