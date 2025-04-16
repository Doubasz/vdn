#include "SDLJeu.h"

int main(void) {
    SDLJeu jeu;

    // Affiche le menu principal
    jeu.renderMainMenu();

    // Si le joueur n’a pas quitté depuis le menu, on lance le jeu
    if (!jeu.isQuit()) {
        jeu.gameLoop();
    }
    

    return 0;
}
