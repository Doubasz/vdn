#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Vec2.h"
#include "Vec2f.h"
#include "Color.h"




void drawBackground(SDL_Renderer*& renderer);
void drawRect(SDL_Renderer*& renderer, SDL_Rect rect, Color color, bool border);
SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path);


#endif