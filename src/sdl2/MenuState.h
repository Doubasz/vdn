#ifndef MENU_STATE_H
#define MENU_STATE_H


#include "GameState.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <cassert>

class MenuState : public GameState {

    enum WindowStat{
        NORMAL, LEVELS, OPTION
    };

private:

    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Texture* background;
    std::vector<Button> buttons;

    std::vector<Button> lvlButtons;

    Mix_Music* music;

    GameState::StateCode whatToDoNow;
    int state;

public:

    MenuState();
    MenuState(SDL_Renderer* renderer, TTF_Font* font);

    ~MenuState();

    void load() override;
    int unload() override;
    void handleEvents(SDL_Event& events) override;
    StateCode update(float dt) override;
    void render(SDL_Renderer* renderer) override;

    void initButtons();
    void renderBackground(SDL_Renderer* renderer);
    void load_music();
    int playBackgroundMusic();
    void renderButtons();
    void renderLevelButtons();

    void loadTextures();

    void startGame();
    void chooseLevel();
    void options();
    void startLevel1();
    void startLevel2();

};

SDL_Texture* loadTextureM(SDL_Renderer* renderer, const char* path);

#endif