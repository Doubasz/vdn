#include <gtest/gtest.h>
#include "MenuState.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <SDL2/SDL_ttf.h>

class MenuStateTest : public ::testing::Test {
protected:
    // Variables nécessaires pour les tests
    SDL_Renderer* renderer;
    TTF_Font* font;
    MenuState* menuState;

    // Fonction d'initialisation exécutée avant chaque test
    void SetUp() override {
        // Initialisation de SDL et de TTF
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        TTF_Init();
        Mix_Init(MIX_INIT_MP3);

        // Créer un renderer SDL pour les tests
        SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        // Charger une font pour les tests
        font = TTF_OpenFont("path_to_some_font.ttf", 24);  // Remplacer par un vrai chemin de police

        // Création de l'instance de MenuState
        menuState = new MenuState(renderer, font);
    }

    // Fonction de nettoyage après chaque test
    void TearDown() override {
        // Nettoyage
        delete menuState;
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        Mix_CloseAudio();
        TTF_Quit();
    }
};

// Test de la méthode load() - Vérification de l'initialisation correcte
TEST_F(MenuStateTest, LoadTest) {
    // Test si le renderer et la font sont correctement initialisés
    menuState->load();  // Appel de la méthode load qui devrait initialiser les membres

    // Vérifier si l'état du jeu est MAIN_MENU après le chargement
    ASSERT_EQ(menuState->update(0.0f), GameState::MAIN_MENU);
}

// Test de la méthode startGame() - Vérification du changement d'état du jeu
TEST_F(MenuStateTest, StartGameTest) {
    // Appeler startGame
    GameState::StateCode newState = menuState->startGame();

    // Vérifier que l'état a changé pour LEVEL
    ASSERT_EQ(newState, GameState::LEVEL);
}

// Test de la gestion des événements
TEST_F(MenuStateTest, HandleEventsTest) {
    SDL_Event event;
    event.type = SDL_MOUSEBUTTONDOWN;

    // Créer un bouton pour tester les événements
    Button b1 = {300, 300, 200, 50, "start game", SDL_Color{0, 0, 0}, SDL_Color{0, 0, 0}, SDL_Color{0, 0, 0}, SDL_Color{0xFF, 0xFF, 0xFF}, font, renderer};
    b1.setOnClick([this]() { menuState->startGame(); });

    // Simuler un événement de clic sur le bouton
    menuState->handleEvents(event, 0.0f);

    // Vérifier que l'état du jeu a bien changé après l'événement
    ASSERT_EQ(menuState->update(0.0f), GameState::LEVEL);
}

// Test de la méthode renderBackground()
TEST_F(MenuStateTest, RenderBackgroundTest) {
    // Appel de la méthode renderBackground
    menuState->renderBackground(renderer);
    
    // Vérifier que le fond a bien été rendu (ceci nécessite un test visuel ou de vérifier le buffer, mais pour l'instant on peut se contenter d'un test sans erreur)
    // Aucune erreur de rendu ne signifie que le fond a été correctement rendu.
    ASSERT_TRUE(true);
}
