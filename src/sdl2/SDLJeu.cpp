

#include "SDLJeu.h"



SDLJeu::SDLJeu(){

    int windowFlags = 0;
    int rendererFlags = SDL_RENDERER_ACCELERATED;

    quit = false;



    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Couldn't init SDL" << std::endl;
        exit(1);
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    //textures = loadAllTexture(renderer);

    /*TTF_Font* fontInit = TTF_OpenFont("/usr/share/fonts/truetype/Gargi/Gargi.ttf", 64);
    if (!fontInit) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(-1);
    }*/

   currentPartie = Partie(DESERT);

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
        currentPartie.deroulementPartie();
        

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
    //currentPartie.handleInput(keys);
}




void SDLJeu::draw(){

    drawPlayer();
    drawBackground();
}


void SDLJeu::drawPlayer(){

    int playerState = currentPartie.getPlayerState();
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
