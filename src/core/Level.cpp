

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

void displayMap(const std::vector<std::vector<int>>& vec){

    std::cout << "GameMap" << std::endl;
    for (const auto& row : vec) {
        for (int tile : row) {
            std::cout << tile << " ";
        }
        std::cout << std::endl;
    }
}

Level::Level(int lvl) : Level(){
    level = lvl;
}



Player& Level::getPlayer() {
    return player;
}

std::vector<Ennemy>& Level::getEnnemies(){
    return ennemies;
}

std::vector<std::vector<int>>& Level::getTileMap(){
    return tileMap;
}

void Level::loadTileMap(){

    std::string path = "";

    switch(level){
        case DESERT:
            path = "src/mapGeneration/map1.txt";
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
            path = "src/mapGeneration/gameMap1.txt";
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


void Level::deroulementLevel(std::string input){

    player.seDeplacer(input);
    player.update();


    checkCollisionPlayerPlatform();
    checkOutOfBonds();

    if(!playerOnPlatform()){
        player.updateGravity();
    }
    else{
        player.resetGravity();
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

        if((playerBottom >= platformPos.y && !(playerBottom > platformPos.y + platformDim.y)) && (playerRight >= platformPos.x && playerLeft <= platformPos.x + platformDim.x)){
            player.changePosition(playerPos.x, platformPos.y - 1);
            return true;
        }
    }
    return false;
}


void Level::checkCollisionPlayerPlatform(){

    Vec2 playerPos = player.getPos();
    Vec2 playerDim = player.getDim();

    int playerBottom = playerPos.y + playerDim.y;
    int playerTop = playerPos.y;
    int playerRight = playerPos.x + playerDim.x;
    int playerLeft = playerPos.x;

    for(Platform p : platforms){
        Vec2 platformPos = p.getPos();
        Vec2 platformDim = p.getDim();

        int platformBottom = platformPos.y + platformDim.y;
        int platformTop = platformPos.y;
        int platformRight = platformPos.x + platformDim.x;
        int platformLeft = platformPos.x;

        /*if(player.getState() == JUMP){
            if(playerTop <= platformBottom && (playerRight >= platformLeft && playerLeft <= platformRight)){
                player.changePosition(playerPos.x, platformPos.y + 1);
            }
        }

        if(playerRight >= platformLeft && (playerTop <= platformBottom && playerBottom >= platformTop)){
            player.changePosition(platformLeft - 1, playerPos.y);
        }
        if(playerLeft >= platformRight && (playerTop <= platformBottom && playerBottom >= platformTop)){
            player.changePosition(platformRight + 1, playerPos.y);
        }*/
    }

    
}

void Level::checkOutOfBonds(){
    Vec2 playerPos = player.getPos();
    Vec2 playerDim = player.getDim();

    if(playerPos.x < 0){
        player.changePosition(0, playerPos.y);
    }
    if(playerPos.x + playerDim.x >= gameMap[0].size()){
        player.changePosition(gameMap[0].size() - playerDim.x, playerPos.y);
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
