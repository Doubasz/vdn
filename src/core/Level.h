#ifndef LEVEL_H
#define LEVEL_H


#include "Player.h"
#include "Ennemy.h"
#include "Platform.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>


enum LevelCode{
    DESERT,
    FOREST,
    CITY,
};

enum Entities{
    NONE = -1,
    PLATFORM,
    PLAYER = -2,
    ENNEMY_TYPE1 = -3,
    ENNEMY_TYPE2 = -4,
    ENNEMY_TYPE3 = -5,
};

enum Tiles{
    SANDBLOCK,
    AIR,
};

class Level{

private:
    int level;
    int score;
    int nbLife;
    bool isLevelCompleted;

    Vec2 dimension;
    std::vector<std::vector<int>> tileMap;
    std::vector<std::vector<int>> gameMap;
 
    Player player;
    std::vector<Ennemy> ennemies;
    std::vector<Platform> platforms;


public:
    Level();
    Level(int lvl);

    void loadTileMap();
    void loadGameMap(int lvl);

    void loadLevel(int lvl);
    void unloadLevel();

    void initEntities();

    void actionAuto();

    void checkCollision();
    void checkOutOfBonds();
    void deroulementLevel(std::string input, float deltaTime);

    Player& getPlayer();
    std::vector<Ennemy>& getEnnemies();
    std::vector<Platform>& getPlatforms();
    std::vector<std::vector<int>>& getTileMap(); 
    std::vector<std::vector<int>>& getGameMap(); 

    bool playerOnPlatform();
    void checkCollisionPlayerPlatform();
    void playerCheckMovement();
    int getPlayerState();
    int getLevel();
    bool isLevelFinished();

    void scale(int x);
};

void displayMap(const std::vector<std::vector<int>>& vec);
bool inBounds(int i, int j, const std::vector<std::vector<int>>& map);
bool neighborIsNone(const std::vector<std::vector<int>>& map, int i, int j);

#endif