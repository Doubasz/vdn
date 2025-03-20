#ifndef JEUTXT_H
#define JEUTXT_H

#include "Partie.h"
#include "Niveau.h"
#include <iostream>


class JeuTxt {
private:
    Partie partie; // Gère les informations liées à la partie (score, joueur, etc.)
    Niveau niveau; // Le niveau actuel du jeu

public:
    // Constructeur par défaut
    JeuTxt();

    // Affiche le niveau et l'état actuel du jeu dans le terminal
    void afficher();

    // Boucle principale du jeu
    void boucleDeJeu();
};

#endif // JEUTXT_H
