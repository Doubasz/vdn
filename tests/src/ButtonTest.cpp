#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Button.h"

// Initialisation de SDL
class SDLTest : public ::testing::Test {
protected:
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

    void SetUp() override {
        SDL_Init(SDL_INIT_VIDEO);
        TTF_Init();
        SDL_Window* window = SDL_CreateWindow("Button Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        font = TTF_OpenFont("path/to/font.ttf", 16);  // Remplacez par le chemin de votre police
    }

    void TearDown() override {
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        TTF_Quit();
    }
};

// Test de création et de rendu du bouton
TEST_F(SDLTest, ButtonCreationAndRendering) {
    Button button(100, 100, 200, 50, "Click Me", {255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}, {255, 255, 255, 255}, font, renderer);
    
    // Vérification de la position initiale
    Rectangle rect = button.getRect();
    EXPECT_EQ(rect.x, 100);
    EXPECT_EQ(rect.y, 100);
    EXPECT_EQ(rect.w, 200);
    EXPECT_EQ(rect.h, 50);

    // Rendu du bouton
    button.render();
}

// Test de la gestion des événements
TEST_F(SDLTest, ButtonHoverAndClick) {
    Button button(100, 100, 200, 50, "Click Me", {255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}, {255, 255, 255, 255}, font, renderer);

    // Simuler le survol de la souris
    SDL_Event e;
    e.type = SDL_MOUSEMOTION;
    e.motion.x = 150;
    e.motion.y = 125;
    button.handleEvent(e);
    
    // L'état doit être en "HOVER"
    EXPECT_EQ(button.getState(), Button::State::HOVER);

    // Simuler un clic sur le bouton
    e.type = SDL_MOUSEBUTTONDOWN;
    e.button.button = SDL_BUTTON_LEFT;
    button.handleEvent(e);
    EXPECT_EQ(button.getState(), Button::State::PRESSED);

    e.type = SDL_MOUSEBUTTONUP;
    button.handleEvent(e);
    EXPECT_EQ(button.getState(), Button::State::HOVER);  // Après le clic, il doit revenir en "HOVER"
}

// Test du changement de texte
TEST_F(SDLTest, ButtonSetText) {
    Button button(100, 100, 200, 50, "Click Me", {255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}, {255, 255, 255, 255}, font, renderer);

    button.setText("New Text");
    // Vérifier que le texte a bien changé
    EXPECT_EQ(button.getText(), "New Text");
}

// Test du changement de couleur
TEST_F(SDLTest, ButtonSetColors) {
    Button button(100, 100, 200, 50, "Click Me", {255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}, {255, 255, 255, 255}, font, renderer);

    button.setColors({0, 255, 255, 255}, {255, 255, 0, 255}, {255, 0, 255, 255});
    // Test de la couleur après le changement
    EXPECT_EQ(button.getNormalColor().r, 0);
    EXPECT_EQ(button.getNormalColor().g, 255);
    EXPECT_EQ(button.getNormalColor().b, 255);
}

// Test de désactivation du bouton
TEST_F(SDLTest, ButtonDisable) {
    Button button(100, 100, 200, 50, "Click Me", {255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}, {255, 255, 255, 255}, font, renderer);
    
    button.setEnabled(false);
    SDL_Event e;
    e.type = SDL_MOUSEBUTTONDOWN;
    e.button.button = SDL_BUTTON_LEFT;
    button.handleEvent(e);
    
    // Le bouton est désactivé, donc il ne doit pas changer d'état
    EXPECT_EQ(button.getState(), Button::State::DISABLED);
}

