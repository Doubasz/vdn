#ifndef MENU_STATE_H
#define MENU_STATE_H


#include "GameState.h"
#include <vector>

class MenuState : public GameState {
private:

    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Texture* background;
    std::vector<Button> buttons;

    GameState::StateCode whatToDoNow;
    int state;

public:

    MenuState();
    MenuState(SDL_Renderer* renderer, TTF_Font* font);

    ~MenuState();

    void load() override;
    int unload() override;
    void handleEvents(SDL_Event& events, float deltaTime) override;
    StateCode update(float dt) override;
    void render(SDL_Renderer* renderer) override;

    void renderBackground(SDL_Renderer* renderer);
    void renderButtons(SDL_Renderer* renderer);

    GameState::StateCode startGame();

};


#endif