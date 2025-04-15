#include "Ennemy.h"





Ennemy::Ennemy() : Entity(), move(0.5){
    dimension = {1, 1};
    velocity = {-1, 0};
    box = {0,0,1,1};
    
    maxFall = 15.3125;
    gravity = 0;

    direction = RIGHT;
    isAlive = true;
    iFrames = 0.4f;
    iFramesTimer = 0;
    hp = 2;
    
    move.reset();
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
void Ennemy::update(float deltaTime) {

    updateIFrames(deltaTime);
    velocity.y += gravity;


    box.setX(box.x + (velocity.x * deltaTime ));
    box.setY(box.y + (velocity.y * deltaTime ));
    
    direction = (velocity.x < 0) ? LEFT : RIGHT;
}

void Ennemy::changeDirection(){
    velocity.x = -velocity.x;
}



bool Ennemy::hitWall(Entity & platform){

    bool onGround = false;
    
   
    if(this->box.overlaps(platform.box)){
        if(this->box.bottom - velocity.y <= platform.box.top){
            this->box.setY(platform.box.top - (this->box.h));
            velocity.y = 0;
            onGround = true;
            
            //std::cout << "Collided with top of platform : " << platform.box.toString() << std::endl;
            //std :: cout << "player pos : " << this->box.toString() << std::endl;
        }
        else if(this->box.rightMost - velocity.x  <= platform.box.leftMost){
            this->box.setX(platform.box.leftMost - (this->box.h));
            
            

            //std::cout << "Collided with left of platform : " << platform.box.toString() << std::endl;
           // std :: cout << "player pos : " << this->box.toString() << std::endl;
            return true;
        }
        else if(this->box.leftMost - velocity.x  >= platform.box.rightMost){
            this->box.setX(platform.box.rightMost );
           
            
            //std::cout << "Collided with right of platform : " << platform.box.toString() << std::endl;
            return true;
        }
        /*else if(this->box.top - velocity.y >= platform.box.bottom ){
            this->box.setY(platform.box.bottom);
            velocity.y = 0;

            std::cout << "Collided with bottom of platform : " << platform.box.toString() << std::endl;
        }*/
    }

    return false;
    
}
bool Ennemy::vaTomber(std::vector<std::vector<int>> &gameMap) {
    Rectangle nextpos = {this->box.x + velocity.x,this->box.y + 1,1,1};
    if(gameMap[nextpos.y][nextpos.x] == -1)
        return true;
    return false;


}


bool Ennemy::nextPosVide(Entity& platform){
    if(this->box.x + velocity.x != platform.box.x)
        return true;
    return false;
}
