#include <gtest/gtest.h>
#include "Timer.h"
#include <thread> // Pour utiliser std::this_thread::sleep_for

// Teste le constructeur et la méthode canProceed
TEST(TimerTest, CanProceedAfterDelay) {
    Timer timer(1.0);
    timer.reset() ;// Un délai de 1 seconde

    // Initialement, le timer ne devrait pas pouvoir procéder (le délai n'est pas encore écoulé)
    EXPECT_FALSE(timer.canProceed());

    // Attendre 1 seconde pour que le timer puisse procéder
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Après 1 seconde, le timer devrait pouvoir procéder
    EXPECT_TRUE(timer.canProceed());
}

// Teste la méthode reset
TEST(TimerTest, ResetWorks) {
    Timer timer(1.0); // Un délai de 1 seconde

    // Attendre un peu de temps pour que le timer puisse procéder
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Avant de réinitialiser, le timer devrait pouvoir procéder
    EXPECT_TRUE(timer.canProceed());

    // Réinitialiser le timer
    timer.reset();

    // Après reset, le timer ne devrait pas pouvoir procéder immédiatement
    EXPECT_FALSE(timer.canProceed());
}

// Teste le cas où le délai est initialisé à 0 (aucun délai)
TEST(TimerTest, ZeroDelay) {
    Timer timer(0.0); // Délai de 0 seconde

    // Le timer devrait pouvoir procéder immédiatement, car le délai est 0
    EXPECT_TRUE(timer.canProceed());

    // Réinitialisation
    timer.reset();
    EXPECT_TRUE(timer.canProceed());
}
