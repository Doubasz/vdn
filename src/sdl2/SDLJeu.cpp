

#include "SDLJeu.h"
#include <string>



SDLJeu::SDLJeu(){

    jeu = Jeu();

    Player& player = jeu.getCurrentLevel().getPlayer();

    int windowFlags = 0;
    int rendererFlags = SDL_RENDERER_ACCELERATED;

    tileSize = 32;

    quit = false;

    


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

    std::vector<std::vector<int>>& gameMap = jeu.getCurrentLevel().getGameMap();

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

    while(!quit){
        frameStart = SDL_GetTicks();

        draw();
        input();
        
        

            // Cap FPS
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);  // Wait for next frame
        }
    }
}



void SDLJeu::input(){

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
        jeu.getCurrentLevel().getPlayer().seDeplacer("q");
        input += "q";
    }
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]){
        jeu.getCurrentLevel().getPlayer().seDeplacer("d");
        input += "d";
    }
    if(keys[SDL_SCANCODE_SPACE]){
        jeu.getCurrentLevel().getPlayer().sauter();
        input += " ";
    }
    jeu.handleInput(input);
}




void SDLJeu::draw(){

    /*std::vector<std::vector<int>> tileMap = jeu.getCurrentLevel().getTileMap();
	Player &player = jeu.getCurrentLevel().getPlayer();
	std::vector<Ennemy> &ennemies = jeu.getCurrentLevel().getEnnemies();

    SDL_Texture* currentTexture;

    for (int x = 0; x < tileMap[0].size(); ++x){
        for (int y = 0; y < tileMap.size(); ++y){

            char c;
            int tile = tileMap[y][x];
            switch(tileMap[y][x]){
                case SANDBLOCK:
                    currentTexture = platformTexture[SANDBLOCK];
                    break;
                case AIR:
                    c = ' ';
                    break;
                default:
                    c = '?';
                    break;
            }
   
        }
    }*/


    drawBackground();
    drawTiles();
    drawPlayer();
    

    SDL_RenderPresent(renderer);
}


void SDLJeu::drawPlayer(){

    SDL_Rect rect = SDL_Rect{32, 32, 32, 32};
    rect.x = jeu.getCurrentLevel().getPlayer().box.x;
    //Log::log("rect.x " + rect.x);
    //std::cout << rect.x << std::endl;
    rect.y = jeu.getCurrentLevel().getPlayer().box.y;
    

    /*int playerState = jeu.getCurrentLevel().getPlayerState();
    drawTexture(renderer, playerTexture[playerState], playerRect);*/

    drawRect(renderer, rect, SDL_Color{0, 255, 0});
}


void SDLJeu::drawTiles(){
    std::vector<std::vector<int>> tileMap = jeu.getCurrentLevel().getTileMap();

    if (tileMap.empty() || tileMap[0].empty()) {
        Log::error("SDLJeu::drawTiles tileMap empty");
        return;
    }

    SDL_Color color;

    SDL_Rect rect = SDL_Rect{0, 0, 32, 32};
    

    for(int i = 0; i < tileMap[0].size(); i++){
        
        for(int j = 0; j < tileMap.size(); j++){

            rect.x = (i * tileSize);
            rect.y = (j * tileSize);

            switch(tileMap[j][i]){
                case SANDBLOCK:
                    color = SDL_Color{200, 100, 0};
                    break;
                case AIR:
                    color = SDL_Color{100, 100, 200};
                    break;
            }

            drawRect(renderer, rect, color);
        }
    }
    
}


void SDLJeu::drawBackground(){

    /*
    SDL_Rect srcRect = {camera.x, camera.y, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};


    SDL_RenderCopy(renderer, background, &srcRect, &destRect);*/

    SDL_SetRenderDrawColor(renderer, 230, 200, 100, 255);
    SDL_RenderClear(renderer);

}


void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& rect){

    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path){
    SDL_Texture* texture;

    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", path);
    Log::log("Loading " + std::string(path));

    texture = IMG_LoadTexture(renderer, path);

    return texture;
}


void SDLJeu::loadPlayerTextures(){

    playerTexture.push_back(loadTexture(renderer, "textures/player.png"));
    playerTexture.push_back(loadTexture(renderer, "textures/pebble.png"));
}

void SDLJeu::loadPlatformTextures(){

    platformTexture.push_back(loadTexture(renderer, "textures/platform.png"));
}

void drawRect(SDL_Renderer*& renderer, SDL_Rect rect, SDL_Color color){

    SDL_SetRenderDrawColor(renderer, color.b, color.g, color.r, 255);
    SDL_RenderFillRect(renderer, &rect);
    
}