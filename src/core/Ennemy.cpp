#include "Ennemy.h"





Ennemy::Ennemy() : Entity(){
    dimension = {1, 1};
    velocity = {0.15, 0};
    box = {0,0,1,1};
    direction = 1; 
}

Ennemy::Ennemy(int x, int y) : Ennemy(){
    position = {x, y};
    box.setX(x);
    box.setY(y);
}

void Ennemy::changePosition(Vec2 pos) {
    position = pos;
    box.setX(pos.x);
    box.setY(pos.y);
}
void Ennemy::changePosition(int x, int y) {
    position = {x, y};
    box.setX(x);
    box.setY(y);
}
void Ennemy::update() {
    position.x += velocity.x * direction;;
    position.y += velocity.y;

    box.setX(position.x);
    box.setY(position.y);
}

void Ennemy::deplacement(bool hitwall){
   
    if(!hitwall ){
        box.setX(box.x + velocity.x * direction);
    }else 
        direction = -direction;
}

bool Ennemy::hitWall(Entity & platform){
    if(this->checkCollision(platform)){
        if(this->box.rightMost - velocity.x <= platform.box.leftMost){
            return true;
        
        }else if(this->box.leftMost - velocity.x >= platform.box.rightMost){
            return true;
            //std::cout << "Collided with right of platform : " << platform.box.toString() << std::endl;
        }
        
    }
       return false;
}


bool Ennemy::nextPosVide(Entity& platform){
    if(this->box.x + velocity.x != platform.box.x)
        return true;
    return false;
}
