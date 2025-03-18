#ifndef NIVEAU_H
#define NIVEAU_H

#include <vector>
#include <string>
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

        

    public :
        Niveau();
        void afficher();
        bool estPositionPersoValide(const int x, const int y)const;
        vector<char> &getGrille();
};


#endif