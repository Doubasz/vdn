#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Timer.h"

/// @brief Represents player power-up or effect states. Not used for now 
enum Etat {
    QAHWA,  ///< Coffee mode – likely increases speed or jump.
    ZETLA,  ///< Special power-up mode – custom effect? 
};

/// @brief Represents the animation or physical state of the player.
enum PlayerState {
    IDLE,
    RUNNING,
    JUMP,
    FALLING,
    ATTACK,
};

/// Constants for movement and physics tuning.
#define ACCEL 0.5f       ///< Ground acceleration.
#define FRICTION 0.3f    ///< Ground friction.
#define GRAVITY 0.8f     ///< Gravity acceleration.
#define MAX_SPEED 5.0f   ///< Maximum horizontal speed.

/// @brief A class representing the main player character.
/// Inherits from `Entity` and handles movement, jumping, attacking,
/// and interaction with enemies and platforms.
class Player : public Entity {

private:
    float accel;              ///< Acceleration factor.
    float friction;           ///< Ground friction.
    float frictionAir;        ///< Air friction.
    float maxSpeed;           ///< Maximum speed the player can move.
    float maxFall;            ///< Maximum fall speed.
    float gravity;            ///< Gravity affecting the player.

    int direction;            ///< LEFT (-1) or RIGHT (1) Might add UP and DOWN ?.
    int state;                ///< Current PlayerState (IDLE, RUNNING, etc).

    // Jumping mechanics
    bool isJumpButtonHeld = false;   ///< True if jump button is currently held.
    float jumpHoldTime;              ///< Time jump has been held.
    float maxJumpHoldTime;           ///< Maximum time jump can be held.
    float minJumpBoost;              ///< Minimum boost added to jump.
    float maxJumpBoost;              ///< Maximum boost added to jump.

    // Attacking
    Rectangle attackHitBox;         ///< Hitbox used during attacks.
    bool isAttacking;               ///< True if currently attacking.
    bool onCoolDown;                ///< True if attack is on cooldown.
    float attackWindow;             ///< Duration of the active attack hitbox.
    float attackTimer;              ///< Timer tracking attack window.
    float attackCooldown;           ///< Time before another attack is allowed.

    // Damage and invincibility
    bool gotHit;                    ///< True if recently damaged.
    float blinkInterval;            ///< For visual feedback (blinking when hit).

    Timer moveTimer;                ///< Timer for movement-related events.

public:
    /// @brief Default constructor.
    Player();

    /// @brief Begins a jump if grounded.
    void jump();

    /// @brief Called when jump button is released to limit jump height.
    void releaseJump();

    /// @brief Updates the jump based on how long the button is held.
    void updateJump(float deltaTime);

    /// @brief Handles movement input ("a", "d", "left", "right", etc).
    void seDeplacer(std::string input);

    /// @brief Initiates an attack if not on cooldown.
    void attack();

    /// @brief Updates the attack timer and cooldown.
    void updateAttack(float deltaTime);

    /// @return True if player is touching ground.
    bool getOnGround() const;

    /// @return True if player has recently taken damage.
    bool getGotHit() const;

    /// @brief Teleports player to given position.
    void changePosition(Vec2 pos);
    void changePosition(int x, int y);

    /// @return True if player's HP > 0.
    bool getIsAlive() const;

    /// @brief Modifies the player's velocity manually.
    void changeVelocity(int x, int y);

    /// @brief Checks collision with a platform.
    bool checkPlatformCollision(Entity& platform);

    /// @brief Checks collision with an enemy and handles damage/knockback.
    void checkCollisionEnnemy(Entity& ennemy, float deltaTime);

    /// @brief Applies gravity to the player.
    void updateGravity();

    /// @brief Disables gravity (e.g., for ladders or floating).
    void resetGravity();

    /// @brief Updates all movement and game logic.
    void update(float deltaTime);

    /// @brief Updates the animation/logic state (IDLE, JUMP, etc).
    void updateState();

    /// @brief Handles left/right movement and acceleration.
    void updateHorizontalMovement(float deltaTime);

    /// @brief Handles jumping and falling motion.
    void updateVerticalMovement(float deltaTime);

    /// @brief Resolves horizontal collision with a platform.
    void checkHorizontalCollision(Entity& platform);

    /// @brief Resolves vertical collision with a platform.
    bool checkVerticalCollision(Entity& platform);

    /// @return Current player state.
    int getState();

    /// @brief Sets jump height boost.
    void setJumpBoost(int j);
    

    /// @return Direction player is facing (LEFT or RIGHT).
    int getDirection() { return this->direction; }

    /// @return True if player was hit recently.
    bool getGotHit() { return this->gotHit; }

    /// @return True if player can take damage (not invincible).
    bool getCanGetHit() { return this->canGetHit; }

    /// @brief Manually set player state.
    void setState(int s) { this->state = s; }

    /// @brief Sets hit state (true if recently damaged).
    void setGotHit(int b) { this->gotHit = b; }

    /// @return Reference to the player's attack hitbox.
    Rectangle& getAttackHitBox() { return this->attackHitBox; }

};

/// @brief Utility to check if a character is in a string.
/// @param input Input string to search.
/// @param target Character to look for.
/// @return True if target is found.
bool contains(std::string input, char target);

#endif
