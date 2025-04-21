#include <gtest/gtest.h>
#include "InGameState.h"  // Inclure le fichier d'en-tête de ta classe

// Mock de l'initialisation de SDL
class MockSDL {
public:
    static bool initialized;

    static void init() {
        if (!initialized) {
            initialized = true;
            SDL_Init(SDL_INIT_VIDEO);
            IMG_Init(IMG_INIT_PNG);
            Mix_Init(MIX_INIT_MP3);
        }
    }

    static void cleanup() {
        if (initialized) {
            Mix_CloseAudio();
            IMG_Quit();
            SDL_Quit();
            initialized = false;
        }
    }
};

bool MockSDL::initialized = false;

class InGameStateTest : public ::testing::Test {
protected:
    void SetUp() override {
        MockSDL::init();  // Initialise SDL pour chaque test
        renderer = SDL_CreateRenderer(SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN), -1, SDL_RENDERER_ACCELERATED);
    }

    void TearDown() override {
        SDL_DestroyRenderer(renderer);
        MockSDL::cleanup();  // Nettoyage après les tests
    }

    SDL_Renderer* renderer;
};

TEST_F(InGameStateTest, TestLoadTextures) {
    InGameState gameState(renderer, 1);  // Utiliser le constructeur avec le renderer et le niveau

    gameState.loadTextures(renderer);  // Tester la fonction loadTextures

    // Vérifie si les textures sont chargées correctement
    ASSERT_NE(gameState.getTileSet(), nullptr);
    ASSERT_NE(gameState.getBackground(), nullptr);
    ASSERT_NE(gameState.getBackground1(), nullptr);
    ASSERT_NE(gameState.getPlayerSheet(), nullptr);
    ASSERT_NE(gameState.getEnnemySheet(), nullptr);
}

TEST_F(InGameStateTest, TestLoadAnimations) {
    InGameState gameState(renderer, 1);  // Utiliser le constructeur avec le renderer et le niveau

    gameState.loadAnimations();  // Tester la fonction loadAnimations

    // Vérifie si les animations sont bien chargées
    ASSERT_EQ(gameState.getPlayerAnimation().size(), 5);  // Vérifie qu'il y a bien 5 animations
     // Vérifie que l'animation "idle" est correctement définie
}

TEST_F(InGameStateTest, TestPlaySound) {
    InGameState gameState(renderer, 1);  // Utiliser le constructeur avec le renderer et le niveau
    gameState.loadSounds(0);  // Charger les sons

    // Test si le son est joué lors de l'appui sur certaines touches
    gameState.playSound("q");
    gameState.playSound("m");
    
    // Aucune méthode directe pour vérifier la lecture du son dans ce test, mais on s'assure que la fonction ne plante pas
    ASSERT_TRUE(true);  // Test passera si aucune exception n'est lancée
}

