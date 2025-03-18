
#ifndef ENNEMI_H

#define ENNEMI_H

#include "Niveau.h"





class Ennemi

{

int x;

int y;

int dir; 



public:



Ennemi();



void bougeAuto(const Niveau &t);



~Ennemi();



};



#endif

