

#include "Draw.h"



SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path){
    SDL_Texture* texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", path);

    texture = IMG_LoadTexture(renderer, path);

    return texture;
}


void drawBackground(SDL_Renderer*& renderer){

    Color bg = Color(0xFF9c7714);

    SDL_SetRenderDrawColor(renderer, bg.b, bg.g, bg.r, 255);
    SDL_RenderClear(renderer);

}


void drawRect(SDL_Renderer*& renderer, SDL_Rect rect, Color color, bool border){

    SDL_SetRenderDrawColor(renderer, color.b, color.g, color.r, 255);
    SDL_RenderFillRect(renderer, &rect);

    if(border){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
    
    
}
