#include <gtest/gtest.h>
#include "Camera.h" // Inclure ta classe Camera

// Fixture pour initialiser une instance de Camera avant chaque test
class CameraTest : public ::testing::Test {
protected:
    Camera camera;

    void SetUp() override {
        // Initialisation de la caméra avec des dimensions et des limites arbitraires
        camera.w = 800;
        camera.h = 600;
        camera.levelWidth = 2000;
        camera.levelHeight = 1500;
        camera.smoothFollow = true;
        camera.followSpeed = 0.1f;
        camera.isShaking = false;
    }
};

// Test pour vérifier le positionnement basique de la caméra
TEST_F(CameraTest, ImmediateFollowPositioning) {
    camera.smoothFollow = false;
    camera.update(1000.0f, 750.0f, 0.016f); // Mise à jour avec une cible au centre du niveau

    EXPECT_FLOAT_EQ(camera.x, 600.0f); // Centrage horizontal (1000 - 800/2)
    EXPECT_FLOAT_EQ(camera.y, 450.0f); // Centrage vertical (750 - 600/2)
}

// Test pour vérifier le positionnement avec SmoothFollow activé
TEST_F(CameraTest, SmoothFollowPositioning) {
    camera.update(1000.0f, 750.0f, 0.016f); // Mise à jour avec SmoothFollow actif

    EXPECT_NE(camera.x, 600.0f); // SmoothFollow signifie que x ne se déplace pas immédiatement
    EXPECT_NE(camera.y, 450.0f);
}

// Test pour vérifier les limites minimales de la caméra
TEST_F(CameraTest, CameraBoundsMinimum) {
    camera.smoothFollow = false;
    camera.update(-100.0f, -100.0f, 0.016f);

    EXPECT_FLOAT_EQ(camera.x, 0.0f); // La caméra ne peut pas sortir du bord gauche
    EXPECT_FLOAT_EQ(camera.y, 0.0f); // La caméra ne peut pas sortir du bord supérieur
}

// Test pour vérifier les limites maximales de la caméra
TEST_F(CameraTest, CameraBoundsMaximum) {
    camera.smoothFollow = false;
    camera.update(3000.0f, 2000.0f, 0.016f);

    EXPECT_FLOAT_EQ(camera.x, 1200.0f); // La caméra ne peut pas dépasser la largeur du niveau
    EXPECT_FLOAT_EQ(camera.y, 900.0f);  // La caméra ne peut pas dépasser la hauteur du niveau
}

// Test pour vérifier l'effet de shake
TEST_F(CameraTest, CameraShake) {
    camera.shake(50.0f, 2.0f); // Déclenche un shake avec intensité 50 et durée 2 secondes

    camera.update(1000.0f, 750.0f, 0.016f); // Appelle update avec un deltaTime

    EXPECT_TRUE(camera.isShaking); // La caméra devrait être en mode shaking
    EXPECT_GT(camera.x, 0.0f);     // Le shake modifie légèrement x
    EXPECT_GT(camera.y, 0.0f);     // Le shake modifie légèrement y
}

// Test pour vérifier l'arrêt du shake
TEST_F(CameraTest, ShakeStopsAfterDuration) {
    camera.shake(50.0f, 2.0f); // Déclenche un shake

    // Simule une mise à jour après la durée du shake
    camera.update(1000.0f, 750.0f, 3.0f); // deltaTime dépasse la durée

    EXPECT_FALSE(camera.isShaking); // Le shake doit s'arrêter après 2 secondes
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
