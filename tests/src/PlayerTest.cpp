#include <gtest/gtest.h>
#include "Player.h"
#include "Entity.h"

class PlayerTest : public ::testing::Test {
protected:
    Player player;
    
    void SetUp() override {
        // Réinitialiser le joueur avant chaque test
        player = Player();
    }
};

// Test du constructeur
TEST_F(PlayerTest, Constructor) {
    EXPECT_EQ(player.getIsAlive(), true);
    EXPECT_EQ(player.getOnGround(), true);
    EXPECT_EQ(player.getState(), IDLE);
    EXPECT_EQ(player.getGotHit(), false);
}

// Test du mouvement horizontal
TEST_F(PlayerTest, HorizontalMovement) {
    // Mouvement vers la droite
    player.seDeplacer("d");
    // Vérifier indirectement que la vitesse a changé en testant l'état
    EXPECT_EQ(player.getState(), RUNNING);
    EXPECT_EQ(player.getDirection(), RIGHT);
    
    // Mouvement vers la gauche
    player.seDeplacer("q");
    EXPECT_EQ(player.getState(), RUNNING);
    EXPECT_EQ(player.getDirection(), LEFT);
    
   
    
   
    // La friction devrait ralentir, mais on ne peut pas tester la valeur directement
}

// Test du saut
TEST_F(PlayerTest, Jump) {
    EXPECT_EQ(player.getOnGround(), true);
    
    // Saut initial
    player.jump();
    EXPECT_EQ(player.getOnGround(), false);
    EXPECT_EQ(player.getState(), JUMP);
    
    // Test du relâchement du saut
    player.releaseJump();
    player.updateJump(0.1f);
    // On teste simplement que la méthode ne cause pas d'erreur
}

// Test de la gravité
TEST_F(PlayerTest, Gravity) {
    player.jump();
    // Test que la gravité fonctionne
    int initialState = player.getState();
    player.updateGravity();
    player.update(0.1f);
    
    // Si on est en mode saut (velocity.y < 0), après assez de gravité,
    // on devrait passer en mode chute (velocity.y > 0)
    // Ce test pourrait nécessiter plusieurs mises à jour
    for (int i = 0; i < 10; i++) {
        player.updateGravity();
        player.update(0.1f);
    }
    
    // Finalement, on devrait être en chute
    EXPECT_EQ(player.getState(), FALLING);
}

// Test de collision avec une plateforme
TEST_F(PlayerTest, PlatformCollision) {
    Entity platform;
    platform.box = Rectangle(10, 20, 10, 2);
    
    // Positionner le joueur au-dessus de la plateforme
    player.changePosition(12, 15);
    player.changeVelocity(0, 5); // Tomber vers la plateforme
    player.setOnGround(false);
    
    bool collision = player.checkPlatformCollision(platform);
    
    EXPECT_TRUE(collision);
    EXPECT_TRUE(player.getOnGround());
    EXPECT_FLOAT_EQ(player.box.top, platform.box.top - player.box.h);
    
}

// Test d'attaque
TEST_F(PlayerTest, Attack) {
    player.attack();
    EXPECT_EQ(player.getState(), ATTACK);
    
    // Vérifier la hitbox d'attaque
    Rectangle& attackHitBox = player.getAttackHitBox();
    EXPECT_GT(attackHitBox.w, 0);
    EXPECT_GT(attackHitBox.h, 0);
    
    // Mettre à jour l'attaque pour qu'elle se termine
    float attackWindow = 0.3f; // Estimation basée sur la classe
    player.updateAttack(attackWindow + 0.1f);
}

// Test de prise de dégâts
TEST_F(PlayerTest, TakeDamage) {
    int initialHp = player.hp;
    Entity enemy;
    enemy.box = Rectangle(player.box.x + 0.5, player.box.y, 1, 1);
    
    player.checkCollisionEnnemy(enemy, 0.1f);
    
    // Si le joueur prend des dégâts, canGetHit devrait devenir false
    if (player.hp < initialHp) {
        EXPECT_FALSE(player.getCanGetHit());
        EXPECT_TRUE(player.getGotHit());
    }
}

// Test de la fonction changePosition
TEST_F(PlayerTest, ChangePosition) {
    player.changePosition(100, 200);
    EXPECT_FLOAT_EQ(player.box.x, 100);
    EXPECT_FLOAT_EQ(player.box.y, 200);
    
   
    player.changePosition(300,400);
    EXPECT_FLOAT_EQ(player.box.x, 300);
    EXPECT_FLOAT_EQ(player.box.y, 400);
}

// Test de la fonction de mise à jour
TEST_F(PlayerTest, Update) {
    player.changeVelocity(5, -5);
    player.setOnGround(false);
    float deltaTime = 0.1f;
    float initialX = player.box.x;
    float initialY = player.box.y;
    
    player.update(deltaTime);
    
    // Vérifier que la position a été mise à jour
    EXPECT_NE(player.box.x, initialX);
    EXPECT_NE(player.box.y, initialY);
    
    // Tester les mises à jour spécifiques
    
}

// Test de modification d'état
TEST_F(PlayerTest, SetState) {
    player.setState(RUNNING);
    EXPECT_EQ(player.getState(), RUNNING);
    
    player.setState(JUMP);
    EXPECT_EQ(player.getState(), JUMP);
}

// Test des fonctions utilitaires
TEST_F(PlayerTest, UtilityFunctions) {
    // Test de la fonction contains
    EXPECT_TRUE(contains("Hello", 'e'));
    EXPECT_FALSE(contains("Hello", 'z'));
    
    // Test setJumpBoost
    int newJumpBoost = -15;
    player.setJumpBoost(newJumpBoost);
    
    // Test setGotHit
    player.setGotHit(true);
    EXPECT_TRUE(player.getGotHit());
    
    player.setGotHit(false);
    EXPECT_FALSE(player.getGotHit());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}