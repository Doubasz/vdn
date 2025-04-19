

#include "Level.h"



Level::Level(){

    score = 0;

    nbLife = 5;
    isLevelCompleted = false;
    player = Player();
    level = DESERT;

    loadGameMap(DESERT);
    loadTileMap();

    //displayMap(gameMap);

    initEntities();
}

Level::Level(int lvl) : Level(){
    level = lvl;
}


void Level::loadLevel(int lvl){

    unloadLevel();

    level = lvl;

    loadGameMap(lvl);
    initEntities();
}

void Level::unloadLevel(){

    score = 0;
    nbLife = 5;
    isLevelCompleted = false;

    tileMap.clear();
    gameMap.clear();

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

void Level::loadGameMap(int lvl){

    std::string path = "";

    switch(lvl){
        case DESERT:
            path = "scripts/mapGeneration/level1.txt";
            break;
        case FOREST:
            path = "scripts/mapGeneration/level2.txt";
            break;
        case CITY:
            path = "scripts/mapGeneration/level3.txt";
            break;
    }

    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Level::loadGameMap : Error: Unable to open file " << path << std::endl;
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

    

    for(int i = 0; i < gameMap[0].size(); i++){
        for(int j = 0; j < gameMap.size(); j++){
            //std:: cout << "x : " << gameMap.size() << " y : " << gameMap[0].size() << std::endl;
            //std::cout<< "i : " << i << " j : " << j << std::endl;
            switch(gameMap[j][i]){
                case PLAYER:
                    player.changePosition(i , j);
                    gameMap[j][i] = NONE;
                    break;
                case ENNEMY_TYPE1:
                    ennemies.push_back(Ennemy(i , j,SCORPION));
                    gameMap[j][i] = NONE;
                    break;
                case ENNEMY_TYPE2:
                    ennemies.push_back(Ennemy(i , j,BATARD));
                    gameMap[j][i] = NONE;

            }

            if(gameMap[j][i] != NONE && gameMap[j][i] != PLAYER && gameMap[j][i] != ENNEMY_TYPE1 && gameMap[j][i] != ENNEMY_TYPE2 ){
                if(neighborIsNone(gameMap, j, i)){
                    platforms.push_back(Platform(i, j));
                }
            }

        }
    }
}


void Level::ennemyMovAuto(float deltaTime) {
    for (Ennemy& e : ennemies) {
        bool isGoingToFall = e.vaTomber(gameMap);
        bool hasHitWall   = false;
        for (Platform& p : platforms) {
            if (e.hitWall(p)) {
                hasHitWall = true;
                break;
            }
        }

        if (e.getType() == BATARD) {
            if (!e.PlayerOutofRange(player)) {

                if (isGoingToFall || hasHitWall) {
                    
                    continue;
                }
    
                e.followPlayer(player);
                e.update(deltaTime);
            }
            else {
                // Hors de portée → agit comme un SCORPION
                if (isGoingToFall) {
                    e.changeDirection();
                }
                for (Platform& p : platforms) {
                    if (e.hitWall(p)) {
                        e.changeDirection();
                        break;
                    }
                }
                e.update(deltaTime);
            }
        }
        else if (e.getType() == SCORPION) {
            if (isGoingToFall) {
                e.changeDirection();
            }
            for (Platform& p : platforms) {
                if (e.hitWall(p)) {
                    e.changeDirection();
                    break;
                }
            }
            e.update(deltaTime);
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
        player.setOnGround(false);
    }
    
    
    for(Ennemy& e : ennemies){
        player.checkCollisionEnnemy(e, deltaTime);
    }
    
    
    ennemyMovAuto(deltaTime);
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
