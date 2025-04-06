

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
            path = "scripts/mapGeneration/level1.txt";
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

// Check if a coordinate is inside the map bounds
bool inBounds(int i, int j, const std::vector<std::vector<int>>& map) {
    return i >= 0 && j >= 0 && i < map.size() && j < map[0].size();
}

// Check if any of the 4 neighbors of (i, j) are NONE
bool neighborIsNone(const std::vector<std::vector<int>>& map, int i, int j) {
    const std::vector<std::pair<int, int>> directions = {
        { -1,  0 }, // north
        {  1,  0 }, // south
        {  0, -1 }, // west
        {  0,  1 }  // east
    };

    for (const auto& [di, dj] : directions) {
        int ni = i + di;
        int nj = j + dj;
        if (inBounds(ni, nj, map) && map[ni][nj] == NONE)
            return true;
    }

    return false;
}

void Level::initEntities(){

    int tileSize = 32;

    for(int i = 0; i < gameMap[0].size(); i++){
        for(int j = 0; j < gameMap.size(); j++){
            //std:: cout << "x : " << gameMap.size() << " y : " << gameMap[0].size() << std::endl;
            //std::cout<< "i : " << i << " j : " << j << std::endl;
            switch(gameMap[j][i]){
                case PLAYER:
                    player.changePosition({i , j});
                    gameMap[j][i] = NONE;
                    break;
                case ENNEMY:
                    ennemies.push_back(Ennemy(i , j));
                    break;
            }

            if(gameMap[j][i] != NONE && gameMap[j][i] != PLAYER && gameMap[j][i] != ENNEMY){
                if(neighborIsNone(gameMap, j, i)){
                    platforms.push_back(Platform(i, j));
                }
            }

        }
    }
}



void Level::deroulementLevel(std::string input, float deltaTime){

    player.seDeplacer(input);

    
    
    // 4. Apply gravity and vertical movement
    player.updateGravity();
    player.update(deltaTime);
    
    // 5. Check vertical collisions
    bool playerOnGround = false;
    for(Platform& p : platforms) {
        if(player.checkPlatformCollision(p)) {
            playerOnGround = true;
        }
        
    }
    
    // 6. Update player state
    if(!playerOnGround) {
        player.setState(JUMP);
    }
    //float deltaTime = 0.016f;
    for(Ennemy& e : ennemies){
        player.checkCollisionEnnemy(e);
    }
    bool hitwall = false;
    for(Ennemy & e : ennemies){
        for(Platform p : platforms){
           hitwall = e.hitWall(p);
        }
        e.update();
    }
    
    
    
    //checkOutOfBonds();

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