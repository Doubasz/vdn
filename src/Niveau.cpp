#include "Niveau.h"
#include <iostream>

const vector<string> grille = {
        "################################################################################",
        "#                                                                              #",
        "#                                                                              #",
        "#                                                                              #",
        "#             #######            ########            #######                   #",
        "#                                                                              #",
        "#                                         E                                    #",
        "#     #######         #######             #######               ########       #",
        "# P                                                            E               #",
        "################################################################################"
    };
Niveau::Niveau(){
    n_dimx = 81;
    n_dimy = 5;
    for (int y = 0 ; y < n_dimy;y++){
        for(int x = 0; x < n_dimx;x++){
            switch (grille[y][x]){
                case '#' : 
                    n_ter[y][x] = PLATEFORME;
                    break;
                case ' ' : 
                    n_ter[y][x] = SPACE;
                    break;
                case 'P' : 
                    n_ter[y][x] = PLAYER;
                    break;
                case 'E' : 
                    n_ter[y][x] = ENEMIE;
                    break;
                
                
            }
        }
    }

}


void Niveau::afficher(){
    for (int y = 0 ; y < n_dimy;y++){
        for(int x = 0; x < n_dimx;x++){
            cout << (char)n_ter[y][x]; 
        }
        cout << endl;
}
}

bool Niveau::estPositionPersoValide(const int x, const int y )const{
    return ((x>= 0) && (x < n_dimx) && (y >= 0) &&  (y < n_dimy) && (n_ter[y][x] != '#'));
}



