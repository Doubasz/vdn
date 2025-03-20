#include "Niveau.h"
#include <iostream>


const vector<string> grille = {
        "################################################################################",
        "#                                                                              #",
        "#                                                                              #",
        "#                                                                              #",
        "#             #######            ########            #######                   #",
        "#                                                                              #",
        "#                                          E                                   #",
        "#     #######         #######             #######               ########       #",
        "#                                                              E               #",
        "################################################################################"
    };
Niveau::Niveau(){
    n_dimx = 81;
    n_dimy = 10;
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

int Niveau::getWidth() const {
    return n_dimx;
}

int Niveau::getHeight() const {
    return n_dimy;
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
 
char Niveau::getCase(const int x, const int y) const {
    if (x >= 0 && x < n_dimx && y >= 0 && y < n_dimy) {
        return (char)n_ter[y][x];
    }
    return '\0'; // Return null character if out of bounds
}

void Niveau::ennemiBougeAuto()

{

for (Ennemi& e : ennemis){

        int dx = (e.getDir() == 1) ? 1 : -1; 
        
        int xtmp = e.getX() + dx; 
        
        int ytmp = e.getY(); 
        
        
        
        
        
        if (estPositionPersoValide(xtmp, ytmp)) {
        
        e.setX(xtmp) ; 
        
        } else {
        
        e.setDir(-e.getDir()); 
        
        }
}

}
