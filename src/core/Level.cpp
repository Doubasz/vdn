

#include "Level.h"



Level::Level(){

    score = 0;

    nbLife = 5;
    isLevelCompleted = false;
    player = Player();
    level = DESERT;

    loadGameMap();
    loadTileMap();

    //displayMap(gameMap);

    initEntities();
}

Level::Level(int lvl) : Level(){
    level = lvl;
}

void displayMap(const std::vector<std::vector<int>>& vec){

    std::cout << "GameMap" << std::endl;
    for (const auto& row : vec) {
        for (int tile : row) {
            std::cout << tile << " ";
        }
        std::cout << std::endl;
    }
}



Player& Level::getPlayer() {
    return player;
}

std::vector<Ennemy>& Level::getEnnemies(){
    return ennemies;
}

std::vector<Platform>& Level::getPlatforms(){
    return platforms;
}

std::vector<std::vector<int>>& Level::getTileMap(){
    return tileMap;
}

std::vector<std::vector<int>>& Level::getGameMap(){
    return gameMap;
}

void Level::loadTileMap(){

    std::string path = "";

    switch(level){
        case DESERT:
            path = "scripts/mapGeneration/map1.txt";
    }

    if(!path.empty()){

        std::ifstream file(path);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << path << std::endl;
            exit(-1);
        }

        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> row;
            std::stringstream ss(line);
            int value;

            while (ss >> value) {
                row.push_back(value);
            }

            tileMap.push_back(row);
        }

        file.close();
    }
}

void Level::loadGameMap(){

    std::string path = "";

    switch(level){
        case DESERT:
            path = "scripts/mapGeneration/gameMap1.txt";
    }

    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << path << std::endl;
        exit(-1);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int value;

        while (ss >> value) {
            row.push_back(value);
        }

        gameMap.push_back(row);
    }

    file.close();
}

void Level::initEntities(){

    for(int i = 0; i < gameMap[0].size(); i++){
        for(int j = 0; j < gameMap.size(); j++){
            switch(gameMap[j][i]){
                case PLAYER:
                    player.changePosition({i, j});
                    break;
                case ENNEMY:
                    ennemies.push_back(Ennemy(i, j));
                    break;
                case PLATFORM:
                    platforms.push_back(Platform(i, j));
            }

        }
    }

}

void Level::actionAuto(){
    for(Ennemy e : ennemies){
        e.moveAuto();
    }
}

void Level::deroulementLevel(std::string input){

    player.update();

    player.seDeplacer(input);

    //playerCheckMovement();


    actionAuto();
    checkCollisionPlayerPlatform();
    checkOutOfBonds();

    if(!playerOnPlatform()){
        player.updateGravity();
    }
    else{
        //player.resetGravity();
    }
}

void Level::playerCheckMovement(){
    Vec2 playerPos = player.getPos();
    Vec2 playerVel = player.getPos();

    if(gameMap[playerPos.x + playerVel.x][playerPos.y + playerVel.y] != NONE){
        player.setVel(0, 0);
    }
}


bool Level::playerOnPlatform(){

    Vec2 playerPos = player.getPos();
    Vec2 playerDim = player.getDim();

    int playerBottom = playerPos.y + playerDim.y;
    int playerRight = playerPos.x + playerDim.x;
    int playerLeft = playerPos.x;


    for(Platform p : platforms){
        Vec2 platformPos = p.getPos();
        Vec2 platformDim = p.getDim();

        if((playerBottom >= platformPos.y && !(playerBottom > platformPos.y + platformDim.y + 1)) && (playerRight >= platformPos.x && playerLeft <= platformPos.x + platformDim.x)){
            player.changePosition(playerPos.x, platformPos.y - playerDim.y - 1);
            return true;
        }
    }
    return false; 
}


void Level::checkCollisionPlayerPlatform() {
    Vec2 playerPos = player.getPos();
    Vec2 playerDim = player.getDim();
    Vec2f playerVel = player.getVel(); // Assuming you add a getVel() method to Entity

    

    // Expanded collision check with more precise collision resolution
    for (Platform& platform : platforms) {
        Vec2 platformPos = platform.getPos();
        Vec2 platformDim = platform.getDim();


        // Collision detection using Axis-Aligned Bounding Box (AABB)
        bool collisionX = (playerPos.x + playerDim.x >= platformPos.x) && 
                          (platformPos.x + platformDim.x >= playerPos.x);
        bool collisionY = (playerPos.y + playerDim.y >= platformPos.y) && 
                          (platformPos.y + platformDim.y >= playerPos.y);

        if (collisionX && collisionY) {
            // Calculate overlap on each axis
            int overlapX = std::min(
                std::abs((playerPos.x + playerDim.x) - platformPos.x),
                std::abs(playerPos.x - (platformPos.x + platformDim.x))
            );
            int overlapY = std::min(
                std::abs((playerPos.y + playerDim.y) - platformPos.y),
                std::abs(playerPos.y - (platformPos.y + platformDim.y))
            );

            // Resolve collision by moving out of the platform
            if (overlapX < overlapY) {
                // Horizontal collision
                if (playerPos.x < platformPos.x) {
                    // Collision from left
                    player.changePosition(platformPos.x - playerDim.x, playerPos.y);
                } else {
                    // Collision from right
                    player.changePosition(platformPos.x + playerDim.x, playerPos.y);
                }
                player.changeVelocity(0, playerVel.y);
            } else {
                // Vertical collision
                if (playerPos.y < platformPos.y) {
                    // Collision from top
                    player.changePosition(playerPos.x, platformPos.y - playerDim.y);
                    player.resetGravity(); // Landing on platform
                } else {
                    // Collision from bottom
                    player.changePosition(playerPos.x, platformPos.y + platformDim.y);
                    player.changeVelocity(playerVel.x, 0);
                }
            }
        }
    }
}

void Level::checkOutOfBonds() {
    Vec2 playerPos = player.getPos();
    Vec2 playerDim = player.getDim();

    // Bord gauche
    if (playerPos.x < 0) {
        player.changePosition(0, playerPos.y);
    }
    // Bord droit
    else if (playerPos.x + playerDim.x >= gameMap[0].size()) {
        player.changePosition(gameMap[0].size() - playerDim.x - 1, playerPos.y); // -1 pour éviter le dépassement
    }

}




int Level::getPlayerState(){
    return player.getState();
}

int Level::getLevel(){
    return level;
}

bool Level::isLevelFinished(){
    return isLevelCompleted;
}


void Level::scale(int x){

    player.setPos(player.getPos().x * x, player.getPos().y * x);
}