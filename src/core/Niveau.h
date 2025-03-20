#ifndef NIVEAU_H
#define NIVEAU_H

#include <vector>
#include <string>
#include "Ennemi.h" // Ensure Ennemi class is defined and included properly
using namespace std;

class Niveau{
        enum TypeCase{
            SPACE = ' ',
            PLATEFORME = '#',
            ENEMIE = 'E',
            PLAYER = 'P'

        };

        int n_dimx,n_dimy;
        TypeCase n_ter[100][100];
        vector<Ennemi> ennemis; // Ensure Ennemi class is correctly defined
        

    public :
        Niveau();
        int getWidth() const;
        int getHeight() const;
        void afficher();
        bool estPositionPersoValide(const int x, const int y)const;
        char getCase(const int x, const int y) const;
        void ennemiBougeAuto();
};

#endif