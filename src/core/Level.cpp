

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

void Level::initEntities() {
    ennemies.clear(); // Nettoyer avant de remplir

    for(int y = 0; y < gameMap.size(); y++) {
        for(int x = 0; x < gameMap[y].size(); x++) {
            switch(gameMap[y][x]) {
                case PLAYER:
                    player.changePosition(x , y );
                  
                    break;
                case ENNEMY:
                    ennemies.push_back(Ennemy(x,y));
                    
                    break;
                case PLATFORM:
                    platforms.push_back(Platform(x,y));
                  
                    break;
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
    // try{

    //         if(gameMap[std::abs(player.getPos().x + player.getVel().x)][std::abs(player.getPos().y + player.getVel().y)] != 0){
    //             std::cout << "prochain pos est " << player.getPos().x/32 + player.getVel().x << " , " << player.getPos().y/32 + player.getVel().y << std::endl;
    //             std::cout <<"size gamemap est de " << gameMap.size() << " , " << gameMap[0].size() << std::endl;
    //             std::cout << "vitesse :: " << player.getVel().x << std::endl;
    //             player.update();
    //         }else{
    //             std::cout << "obstacle" << std::endl;
    //         }
    // }
    // catch (const std::exception& e){

    //     std::cerr << "Exception caught: " << e.what() << std::endl;
    //     std::cout << "prochain pos est " << player.getPos().x + player.getVel().x << " , " << player.getPos().y + player.getVel().y << std::endl;
    //     std::cout <<"size gamemap est de " << gameMap.size() << " , " << gameMap[0].size() << std::endl;
    //     std::cout << "vitesse :: " << player.getVel().x << std::endl;
    // }
    
    player.checkAndUpdate(gameMap);
    player.seDeplacer(input);

    //playerCheckMovement();


    actionAuto();
    
    checkOutOfBonds();

    if(!playerOnPlatform()){
        player.updateGravity();
    }
    else{
        //player.resetGravity();
    }
}



bool Level::playerOnPlatform() {
    const Vec2 playerPos = player.getPos();
    const Vec2 playerDim = player.getDim();
    const Vec2 playerFeet = {playerPos.x + playerDim.x / 2, playerPos.y + playerDim.y};
    const float detectionRange = 0.0f; // Tolérance en pixels

    for (const Platform& p : platforms) {
        const Vec2 platformPos = p.getPos();
        const Vec2 platformDim = p.getDim();

        // Vérifie si le joueur est dans la largeur de la plateforme
        const bool xCollision = (playerPos.x + playerDim.x > platformPos.x) && 
                                (playerPos.x < platformPos.x + platformDim.x);
        
        // Vérifie si les pieds du joueur touchent le haut de la plateforme
        const bool yCollision = (playerFeet.y >= platformPos.y) && 
                                (playerFeet.y <= platformPos.y + detectionRange);

        if (xCollision && yCollision) {
            // Vérifie si le joueur tombe avant de le repositionner
            if (player.getVel().y >= 0) {
                player.setPos(playerPos.x, platformPos.y - playerDim.y);
                player.resetGravity(); //    Remet la vitesse verticale à zéro
                player.setIsgrounded(true);
                return true;
            }
        }
    }

    player.setIsgrounded(false);
    return false;
}




void Level::checkOutOfBonds() {
    Vec2 playerPos = player.getPos();
    Vec2 playerDim = player.getDim();

    // Bord gauche
    if (playerPos.x < 0) {
        player.changePosition(0, playerPos.y);
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