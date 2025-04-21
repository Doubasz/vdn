#include <gtest/gtest.h>
#include "Level.h"
#include "Player.h"
#include "Ennemy.h"
#include "Platform.h"

// Fixture pour les tests de la classe Level
class LevelTest : public ::testing::Test {
protected:
    Level level;

    // Setup pour chaque test (réinitialisation de l'état si nécessaire)
    void SetUp() override {
        level = Level(); // Initialisation du niveau
    }

    void SetUp(int lvl) {
        level = Level(lvl); // Initialisation du niveau avec un niveau spécifique
    }

    // Exemple de fonction pour créer un mock de Player si nécessaire
    Player& getPlayer() {
        return level.getPlayer();
    }

    std::vector<Ennemy>& getEnnemies() {
        return level.getEnnemies();
    }

    std::vector<Platform>& getPlatforms() {
        return level.getPlatforms();
    }

    std::vector<std::vector<int>>& getTileMap() {
        return level.getTileMap();
    }

    std::vector<std::vector<int>>& getGameMap() {
        return level.getGameMap();
    }
};

// Test pour vérifier l'initialisation du niveau
TEST_F(LevelTest, DefaultConstructor) {
    EXPECT_EQ(level.getLevel(), DESERT); // Niveau par défaut : DESERT
    EXPECT_EQ(level.getPlayerState(), 0); // Etat initial du joueur
    EXPECT_FALSE(level.isLevelFinished()); // Le niveau ne devrait pas être terminé au début
}

// Test pour vérifier le changement de niveau
TEST_F(LevelTest, LoadAndUnloadLevel) {
    level.loadLevel(FOREST); // Charger le niveau FOREST
    EXPECT_EQ(level.getLevel(), FOREST); // Vérifier que le niveau a changé

    level.unloadLevel(); // Décharger le niveau
    EXPECT_EQ(level.getLevel(), DESERT); // Vérifier que le niveau par défaut est rétabli
}

// Test pour vérifier le comportement du joueur dans le niveau
TEST_F(LevelTest, PlayerPositionChange) {
    Player& player = getPlayer();
    player.changePosition(10, 20); // Déplacer le joueur à la position (10, 20)
    
    EXPECT_EQ(player.getBox().x, 10); // Vérifier la position X
    EXPECT_EQ(player.getBox().y, 20); // Vérifier la position Y
}

// Test pour vérifier l'ajout des ennemis dans le niveau
TEST_F(LevelTest, EnnemyPlacement) {
    // Charger un niveau spécifique avec des ennemis
    level.loadGameMap(DESERT); 
    
    // Vérifier qu'il y a des ennemis dans le niveau
    std::vector<Ennemy>& ennemies = getEnnemies();
    EXPECT_GT(ennemies.size(), 0); // Vérifier qu'il y a au moins un ennemi
    
    // Vérifier que chaque ennemi a bien été placé
    for (const Ennemy& e : ennemies) {
        EXPECT_TRUE(e.getBox().x >= 0 && e.getBox().y >= 0); // Vérifier que les ennemis ont une position valide
    }
}

// Test pour vérifier l'ajout des plateformes
TEST_F(LevelTest, PlatformPlacement) {
    // Charger un niveau avec des plateformes
    level.loadGameMap(DESERT);
    
    std::vector<Platform>& platforms = getPlatforms();
    EXPECT_GT(platforms.size(), 0); // Vérifier qu'il y a au moins une plateforme
    
    // Vérifier que chaque plateforme a bien été placée
    for (const Platform& p : platforms) {
        EXPECT_TRUE(p.getBox().x >= 0 && p.getBox().y >= 0); // Vérifier que les plateformes ont une position valide
    }
}

// Test pour vérifier le mouvement des ennemis
TEST_F(LevelTest, EnnemyMovement) {
    level.loadGameMap(DESERT); // Charger un niveau avec des ennemis
    std::vector<Ennemy>& ennemies = getEnnemies();
    
    float deltaTime = 0.016f; // Exemple de deltaTime (60 FPS)
    for (Ennemy& e : ennemies) {
        float initialX = e.getBox().x;
        e.update(deltaTime); // Mettre à jour la position de l'ennemi
        
        // Vérifier que l'ennemi a bougé
        EXPECT_NE(e.getBox().x, initialX); // Vérifier que la position X a changé
    }
}

// Test pour vérifier que la détection de chute fonctionne
TEST_F(LevelTest, FallDetection) {
    level.loadGameMap(DESERT); // Charger un niveau avec une carte de jeu

    // Exemple de position pour un ennemi
    Ennemy e(5, 5, SCORPION); 
    std::vector<std::vector<int>>& gameMap = getGameMap();

    // Tester si l'ennemi tombe
    bool fallDetected = e.vaTomber(gameMap);
    EXPECT_TRUE(fallDetected); // Vérifier que l'ennemi détecte une chute
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
