

#include "SDLJeu.h"



SDLJeu::SDLJeu(){

    jeu = Jeu();

    int windowFlags = 0;
    int rendererFlags = SDL_RENDERER_ACCELERATED;

    quit = false;



    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        Log::error("SDLJeu::SDLJeu() Couldn't init SDL");
        Log::error(std::string (SDL_GetError()));
        exit(1);
    }

    if (TTF_Init() == -1) {
        Log::error("SDLJeu::SDLJeu() Couldn't init TTF");
        Log::error(std::string (TTF_GetError()));
        exit(1);
    }

    window = SDL_CreateWindow("Vent du Nord", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);


    loadPlayerTextures();

    //textures = loadAllTexture(renderer);

    /*TTF_Font* fontInit = TTF_OpenFont("/usr/share/fonts/truetype/Gargi/Gargi.ttf", 64);
    if (!fontInit) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(-1);
    }*/

   currentLevel = Level(DESERT);

}



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

    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]){
        input += 'd';
    }
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]){
        input += 'q';
    }
    if(keys[SDL_SCANCODE_SPACE]){
        input += ' ';
    }
    currentLevel.deroulementLevel(input);
}




void SDLJeu::draw(){

    std::vector<std::vector<int>> tileMap = jeu.getCurrentLevel().getTileMap();
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
    }


    drawPlayer();
    drawBackground();
}


void SDLJeu::drawPlayer(){

    int playerState = currentLevel.getPlayerState();
    drawTexture(renderer, playerTexture[playerState], playerRect);
}


void SDLJeu::drawBackground(){

    // Define the portion of the background to render
    SDL_Rect srcRect = {camera.x, camera.y, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // Render the background
    SDL_RenderCopy(renderer, background, &srcRect, &destRect);
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

    for(int i = 0; i < PLAYER_TEXTURE; i++){
        SDL_Texture* temp = loadTexture(renderer, PLAYER_TEXTURE[i]);
        playerTexture.push_back(temp);
    }
}