/*#ifndef NIVEAU_H
#define NIVEAU_H

#include <vector>
#include <string>
#include "Ennemi.h"
 
using namespace std;

enum TypeCase{
    SPACE = ' ',
    PLATEFORME = '#',
    ENEMIE = 'E',
    PLAYER = 'P'

};

class Niveau{
        

        int n_dimx,n_dimy;
        std::vector<int> tileMap;
        vector<Ennemi> ennemis;
        

    public :
        Niveau();
        int getWidth() const;
        int getHeight() const;
        void afficher();
        bool estPositionPersoValide(const int x, const int y)const;
        char getCase(const int x, const int y) const;
        void ennemiBougeAuto();
};

#endif*/