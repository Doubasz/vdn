#ifndef ENNEMY_H
#define ENNEMY_H

#include "Entity.h"
#include "Timer.h"

/// @enum TypeEnnemy
/// @brief Different types of enemies.
enum TypeEnnemy {
    SCORPION,   ///< Desert enemy
    BATARD,     ///< Urban enemy
};

/// @class Ennemy
/// @brief Represents an enemy in the game.
///
/// Inherits from Entity and adds enemy-specific behavior such as automatic movement and simple AI.
class Ennemy : public Entity {

private:
    int direction;       ///< Current direction (LEFT or RIGHT)
    int type;            ///< Type of the enemy (see TypeEnnemy enum)
    float gravity;       ///< Gravity affecting the enemy
    float maxFall;       ///< Maximum falling speed
    int state;           ///< Enemy state (e.g., idle, moving)

    Timer move;          ///< Timer controlling movement intervals

public:

    /// @brief Default constructor.
    Ennemy();

    /// @brief Constructs an enemy at the specified position and type.
    /// @param x X-coordinate
    /// @param y Y-coordinate
    /// @param type Type of the enemy (see TypeEnnemy)
    Ennemy(int x, int y, int type);

    /// @brief Changes the position using a Vec2 object.
    /// @param pos New position.
    void changePosition(Vec2 pos);

    /// @brief Changes the position using X and Y values.
    /// @param x New X position.
    /// @param y New Y position.
    void changePosition(int x, int y);

    /// @brief Changes the movement direction.
    void changeDirection();

    /// @brief Automatically moves the enemy based on its type and direction.
    void moveAuto();

    /// @brief Updates enemy state, movement, and physics.
    /// @param deltaTime Time elapsed since last frame.
    void update(float deltaTime);

    /// @brief Manages movement based on wall collisions.
    /// @param hitwall Whether the enemy has hit a wall.
    void deplacement(bool hitwall);
    int getType() const;
    bool PlayerOutofRange(Entity &player)const;
    void followPlayer(Entity &player);

    /// @brief Checks if the enemy is colliding with a wall.
    /// @param platform The platform to check against.
    /// @return True if hitting a wall, false otherwise.
    bool hitWall(Entity& platform);

    /// @brief Checks if the enemy is about to fall off the platform.
    /// @param gameMap The map grid to analyze.
    /// @return True if the next step is empty (falling), false otherwise.
    bool vaTomber(std::vector<std::vector<int>>& gameMap);

    /// @brief Checks if the next position is empty.
    /// @param platform Platform to check.
    /// @return True if the next position is empty.
    bool nextPosVide(Entity& platform);

    /// @brief Gets the enemy's current direction.
    /// @return Direction (LEFT or RIGHT).
    int getDirection() { return direction; }
};

#endif // ENNEMY_H