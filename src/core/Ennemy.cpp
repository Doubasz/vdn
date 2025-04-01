#include "Ennemy.h"

Ennemy::Ennemy() : Entity() {
    dimension = {32, 32}; // Taille standard
    velocity = {1, 0}; // Vitesse de base
    type = SCORPION;
}

Ennemy::Ennemy(int x, int y) : Ennemy() {
    position = {x * 32, y * 32}; // Conversion en pixels
}

void Ennemy::update() {
    position.x += velocity.x;
    position.y += velocity.y;
}

void Ennemy::moveAuto() {
    // Mouvement de va-et-vient plus fluide
    if (movingRight) {
        position.x += 2;
        if (++moveCounter > 60) { // Après 60 frames
            movingRight = false;
            moveCounter = 0;
        }
    } else {
        position.x -= 2;
        if (++moveCounter > 60) {
            movingRight = true;
            moveCounter = 0;
        }
    }
}

void Ennemy::changePosition(int x, int y) {
    position = {x, y};
}