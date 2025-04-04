#ifndef LEVEL_H
#define LEVEL_H


#include "Player.h"
#include "Ennemy.h"
#include "Platform.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>


enum Niveauu{
    DESERT,
    FORET,
    VILLE
};

enum Entities{
    NONE = -1,
    PLATFORM,
    PLAYER,
    ENNEMY,
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
    void loadGameMap();

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

#endif