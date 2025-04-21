#ifndef ENTITY_H
#define ENTITY_H

#include "Vec2.h"
#include "Vec2f.h"
#include "Shapes.h"
#include <algorithm>

/// Direction enum used for movement logic, knockbacks, etc.
enum Directions {
    LEFT,
    RIGHT,
    UP,
    DOWN,
};


/// Base class representing any game object with a position, size, health, and physics.
///
/// This class defines a rectangular-shaped entity with position, velocity, and collision logic.
/// Entities can also take damage, experience knockback, and be toggled as visible or invisible.
///
/// ## How to use
///
///     // Inherit from Entity
///     class Player : public Entity { ... };
///
///     // Set position, size, and velocity
///     entity.setPos(100, 200);
///     entity.setDim(50, 50);
///     entity.setVel(1, 0);
///
///     // Check collision
///     if (entity.checkCollision(enemy)) { ... }
///
class Entity {
public:

    Rectangle box;      ///< Bounding box for position and dimension.
    int hp;             ///< Health points of the entity.
    bool isAlive;       ///< Whether the entity is currently active.
    float iFrames;      ///< Duration of invincibility frames after hit.
    float iFramesTimer; ///< Timer to track iFrames.
    bool canGetHit;     ///< Whether the entity is currently vulnerable.
    bool isVisible;     ///< Whether the entity is currently visible on screen.

protected:

    Vec2f velocity;     ///< 2D velocity (floating point precision).
    bool onGround;      ///< Whether the entity is on the ground.

    float knockBackTimer;      ///< Timer for knockback duration.
    float knockBackDuration;   ///< Total time for knockback.
    float knockBackForce;      ///< Intensity of knockback.
    float knockBackFriction;   ///< Resistance during knockback.
    bool onKnockBack;          ///< Whether the entity is currently knocked back.

public:

    /// Default constructor.
    Entity();

    /// Construct an entity with position, size, and velocity.
    Entity(int x, int y, int w, int h, float vx, float vy);

    /// Construct an entity from vector-based parameters.
    Entity(Vec2 pos, Vec2 dim, Vec2f vel);

    /// Virtual destructor to allow polymorphic deletion.
    virtual ~Entity();

    /// Get the current velocity.
    Vec2f getVel() const { return velocity; }

    /// Set entity position.
    void setPos(int x, int y);

    /// Set entity dimensions (width and height).
    void setDim(int x, int y);

    /// Set velocity.
    void setVel(int x, int y);

    /// Set health points.
    void setHp(int h);

    /// Get current health.
    int getHp();

    /// Decrease health by 1.
    void decreaseHp();

    /// Increase health by 1.
    void increaseHp();

    /// General AABB collision check with another entity.
    bool checkCollision(const Entity& other) const;

    /// Check for collision specifically on the top side.
    bool checkCollisionWithTop(const Entity& other);

    /// Update invincibility frame logic.
    void updateIFrames(float deltaTime);

    /// Update knockback logic and position changes.
    void updateKnockBack(float deltaTime);

    /// Apply knockback to the entity with force and duration.
    void applyKnockBack(float force, float duration);

    /// Get the bounding box.
    Rectangle getBox() const { return this->box; }

    /// Get whether the entity is visible.
    bool getIsVisible() const { return this->isVisible; }

    /// Set whether the entity is grounded.
    void setOnGround(int b) { this->onGround = b; }
};

#endif // ENTITY_H
