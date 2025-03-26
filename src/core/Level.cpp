

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
    std::cout << "prochain pos est " << player.getPos().x + player.getVel().x << " , " << player.getPos().y + player.getVel().y << std::endl;
    std::cout <<"size gamemap est de " << gameMap[0].size() << " , " << gameMap.size() << std::endl;
    std::cout << "vitesse :: " << player.getVel().x << std::endl;
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
    Vec2 playerPos = player.getPos();
    Vec2 playerDim = player.getDim();

    // Ajustez ces valeurs si nécessaire
    int playerBottom = playerPos.y + playerDim.y;
    int playerRight = playerPos.x + playerDim.x;
    int playerLeft = playerPos.x;

    for (Platform& p : platforms) {
        Vec2 platformPos = p.getPos();
        Vec2 platformDim = p.getDim();

        // Conditions de collision plus tolérantes
        bool horizontalOverlap = 
            playerRight > platformPos.x && 
            playerLeft < platformPos.x + platformDim.x;

        bool verticalContact = 
            playerBottom >= platformPos.y && 
            playerBottom <= platformPos.y + 3; // Augmentez cette valeur pour plus de tolérance

        if (horizontalOverlap && verticalContact) {
            // Repositionnement précis
            player.changePosition(playerPos.x, platformPos.y - playerDim.y);
            player.resetGravity(); // Réinitialise la gravité
            return true;
        }
    }
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