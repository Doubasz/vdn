#ifndef LEVEL_H
#define LEVEL_H


#include "Player.h"
#include "Ennemy.h"
#include "Platform.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>


/// @brief Codes representing different level environments.
enum LevelCode{
    DESERT,
    FOREST,
    CITY,
};

/// @brief Codes used to represent game entities in the game map.
enum Entities{
    NONE = -1,
    PLATFORM,
    PLAYER = -2,
    ENNEMY_TYPE1 = -3,
    ENNEMY_TYPE2 = -4,
    ENNEMY_TYPE3 = -5,
};

/// @brief Tile types in the level map.
enum Tiles{
    SANDBLOCK,
    AIR,
};

/// @brief Represents a game level including the player, platforms, enemies, and maps.
class Level{

private:
    int level; ///< Current level number.
    int score; ///< Player score.
    int nbLife; ///< Number of player lives.
    bool isLevelCompleted; ///< Whether the level has been completed.

    Vec2 dimension; ///< Dimensions of the level.
    std::vector<std::vector<int>> tileMap; ///< Map representing terrain tiles.
    std::vector<std::vector<int>> gameMap; ///< Map representing entities.
 
    Player player; ///< Player object.
    std::vector<Ennemy> ennemies; ///< List of enemies in the level.
    std::vector<Platform> platforms; ///< List of platforms in the level.


public:
    /// @brief Default constructor.
    Level();
    /// @brief Constructs a level with a given number.
    Level(int lvl);

    /// @brief Loads the tile map from file.
    void loadTileMap();
    /// @brief Loads the game entity map from file for a given level.
    void loadGameMap(int lvl);

    /// @brief Loads all level data.
    void loadLevel(int lvl);
    /// @brief Clears level data.
    void unloadLevel();

    /// @brief Initializes all entities (player, enemies, platforms).
    void initEntities();

    /// @brief Updates all autonomous actions (e.g. enemy AI).
    void actionAuto();

    /// @brief Checks collisions between all entities.
    void checkCollision();
    /// @brief Checks if any entities went out of bounds.
    void checkOutOfBonds();

    void ennemyMovAuto(float deltaTime);
    void deroulementLevel(std::string input, float deltaTime);

    /// @brief Gets the player.
    Player& getPlayer();
    /// @brief Gets the enemies.
    std::vector<Ennemy>& getEnnemies();
    /// @brief Gets the platforms.
    std::vector<Platform>& getPlatforms();
    /// @brief Gets the tile map.
    std::vector<std::vector<int>>& getTileMap(); 
    /// @brief Gets the entity map.
    std::vector<std::vector<int>>& getGameMap(); 

    /// @brief Checks if the player is currently on a platform.
    bool playerOnPlatform();
    /// @brief Handles collision detection between the player and platforms.
    void checkCollisionPlayerPlatform();
    /// @brief Handles player's movement logic.
    void playerCheckMovement();

    /// @brief Returns the current state of the player.
    int getPlayerState();
    /// @brief Returns the current level number.
    int getLevel();
    /// @brief Returns whether the level is completed.
    bool isLevelFinished();

    /// @brief Scales the level (useful for resizing, zooming, etc).
    void scale(int x);
};

/// @brief Displays a 2D map in the console.
/// @param vec The map to display.
void displayMap(const std::vector<std::vector<int>>& vec);

/// @brief Checks if the given indices are inside the bounds of the map.
/// @param i Row index.
/// @param j Column index.
/// @param map The map.
/// @return True if in bounds, false otherwise.
bool inBounds(int i, int j, const std::vector<std::vector<int>>& map);

/// @brief Checks if a neighboring cell of a map tile is empty.
/// @param map The map.
/// @param i Row index.
/// @param j Column index.
/// @return True if a neighboring tile is NONE, false otherwise.
bool neighborIsNone(const std::vector<std::vector<int>>& map, int i, int j);

#endif
