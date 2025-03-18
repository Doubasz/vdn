#include "Ennemi.h"





Ennemi::Ennemi(){

x=1;

y=1; 

dir=0;

}



void Ennemi::bougeAuto(const Niveau &t)

{


int dx = (dir == 1) ? 1 : -1; 

int xtmp = x + dx; 

int ytmp = y; 





if (t.estPositionPersoValide(xtmp, ytmp)) {

x = xtmp; 

} else {

dir = -dir; 

}

}


