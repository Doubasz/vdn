

#include "Jeu.h"
#include "Vec2.h"


Jeu::Jeu(){

    int windowFlags = 0;
    int rendererFlags = SDL_RENDERER_ACCELERATED;



    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Couldn't init SDL" << std::endl;
        exit(1);
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, windowFlags);
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    //textures = loadAllTexture(renderer);

    TTF_Font* fontInit = TTF_OpenFont("/usr/share/fonts/truetype/Gargi/Gargi.ttf", 64);
    if (!fontInit) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(-1);
    }
}



void Jeu::draw(){
    drawBackground(renderer);

    //currentPartie.draw();
}



void Jeu::input(){

    Vec2 mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);

    SDL_Event event;

    while(SDL_PollEvent(&event)){

        switch(event.type){
            case SDL_QUIT:
                quit = true;
                exit(0);
                break;
        }
    }
}

void Jeu::gameLoop(){

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
