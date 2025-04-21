

#include "Level.h"



Level::Level(){

    score = 0;

    nbLife = 5;
    isLevelCompleted = false;
    player = Player();
    level = DESERT;

    loadGameMap(level);
    

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

    ennemies.clear();
    platforms.clear();

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



std::vector<std::vector<int>>& Level::getGameMap(){
    return gameMap;
}


void Level::loadGameMap(int lvl){

    std::string path = "";

    switch(lvl){
        case DESERT:
            path = "scripts/mapGeneration/leveldesert.txt";
            break;
        case FOREST:
            path = "scripts/mapGeneration/level1.txt";
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
    return i >= 0 && j >= 0 &&
           static_cast<size_t>(i) < map.size() &&
           static_cast<size_t>(j) < map[0].size();
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

    

    for(size_t i = 0; i < gameMap[0].size(); i++){
        for(size_t j = 0; j < gameMap.size(); j++){
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
                e.setVel(1.5,0);
                e.followPlayer(player);
                e.update(deltaTime);
            }
            else {
                e.setVel(1,0);
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



bool Level::finJeu(){
    if(level == FOREST){
        if(isLevelCompleted)
            return true;
        
    }
    return false;
}

void Level::deroulementLevel(std::string input, float deltaTime){

    isLevelCompleted = finLevel(player);
    if( isLevelCompleted){
        if(level == DESERT)
            level = FOREST;
    }

    
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
        player.checkCollisionEnnemy(e);
    }
    
    
    ennemyMovAuto(deltaTime);
}









int Level::getPlayerState(){
    return player.getState();
}

int Level::getLevel(){
    return level;
}

bool Level::finLevel (Player& player){
    if(level == DESERT ){
        if(player.getBox(). x > 199.8){
            return true;
        }
        return false;
    }else if(level == FOREST){
        if(player.getBox().x > 59.8){
            return true;
        }
        return false;
    }
    return false;
}

bool Level::isLevelFinished(){
    return isLevelCompleted;
}
