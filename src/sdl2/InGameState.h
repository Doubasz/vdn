#ifndef IN_GAME_STATE_H
#define IN_GAME_STATE_H

#include <SDL2/SDL_mixer.h>
#include "GameState.h"
#include "../core/Jeu.h"
#include "../core/Camera.h"
#include "Button.h"


enum WindowState{
    CONTINUE, PAUSE, QUIT,
};

struct Animation{
    int startFrame;    
    int numFrames;      
    int currentFrame;   
    float frameTime;    
    float timer;     
    bool loop;
};




class InGameState : public GameState{

private:

    SDL_Renderer* renderer;
    int level;

    Jeu jeu;

    SDL_Texture* background;
    SDL_Texture* background1;
    SDL_Texture* tileSet;

    SDL_Texture* playerSheet;
    SDL_Rect playerRect;

    std::vector<Animation> playerAnimation;

    Animation currentAnimation;

    std::vector<SDL_Texture*> platformTexture;

    std::vector<Button> buttons;

    SDL_Texture* ennemySheet;

    TTF_Font* font;
    SDL_Color textColor;

    Animation ennemyAnimation;

    Camera camera;

    Mix_Chunk* sauter;
    Mix_Chunk* gotHit;
    Mix_Chunk* walk;
    Mix_Chunk* attack;
    Mix_Chunk* land;
    Mix_Music* music;

    Timer moveTimer;
    Timer attacksound;

    
    int tileSize;
    int state;

    int blinkInterval;

    int lastPlayerState;

    bool quit;

public:

    InGameState();
    InGameState(SDL_Renderer* renderer, TTF_Font* font, int lvl);

    void load() override;
    int unload() override;
    void handleEvents(SDL_Event& events, float deltaTime) override;
    StateCode update(float dt) override;
    void render(SDL_Renderer* renderer) override;

    void renderPlayer(SDL_Renderer* renderer);  
    void renderEnnemy(SDL_Renderer* renderer);  
    void renderTiles(SDL_Renderer* renderer);  
    void renderBackground(SDL_Renderer* renderer);  
    void renderLives(SDL_Renderer* renderer);   
    void renderTimer(SDL_Renderer* renderer);  

    void loadTextures(SDL_Renderer* renderer);
    void loadAnimations();

    void updateGame(float deltaTime);
    void updateAnimation(float deltaTime);
    void updateEnnemyAnimation(float deltaTime);
    void updateCamera(float deltaTime);

    int playBackgroundMusic(int niveau) ;
    void playSound(std::string input);
    int loadSounds(int niveau);

    void initButtons();

    void resumeGame();
    void quitGame();

    void renderButtons();
    

};

SDL_Texture* loadTexture(SDL_Renderer* renderer, char* path);

#endif