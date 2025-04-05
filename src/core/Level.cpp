

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
            path = "scripts/mapGeneration/map3.txt";
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
            path = "scripts/mapGeneration/gameMap4.txt";
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

    int tileSize = 32;

    for(int i = 0; i < gameMap[0].size(); i++){
        for(int j = 0; j < gameMap.size(); j++){
            switch(gameMap[j][i]){
                case PLAYER:
                    player.changePosition({i , j });
                    break;
                case ENNEMY:
                    ennemies.push_back(Ennemy(i , j ));
                    break;
                case PLATFORM:
                    platforms.push_back(Platform(i , j ));
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

    player.seDeplacer(input);
    player.updateGravity();
    player.update();

    //playerCheckMovement();
    
    


    bool playerOnGround = false;
    //actionAuto();
    for(Platform p : platforms){
        if(player.checkCollisionPlatform(p)){
            playerOnGround = true;
        }
    }

    if(!playerOnGround){
        player.setState(JUMP);
    }
    
    //checkOutOfBonds();

}

void Level::playerCheckMovement(){
    Vec2 playerPos = player.getPos();
    Vec2 playerVel = player.getPos();

    if(gameMap[playerPos.x + playerVel.x][playerPos.y + playerVel.y] != NONE){
        player.setVel(0, 0);
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