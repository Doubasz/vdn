#ifndef PLATFORM_H
#define PLATFORM_H

#include "Entity.h"

/// @brief Types of platform tiles available in the game.
enum TypeTile {
    SAND,  ///< Sandy platform tile (desert environment, soft look).
    ROCK,  ///< Rocky platform tile (solid ground, maybe mountainous or cave).
};

/// @brief A class representing a static platform that the player or enemies can stand on.
/// Inherits from `Entity` for collision, position, and physics data.
///
/// Might add moving and falling platforms ?
class Platform : public Entity {

private:
    int type;  ///< Type of tile used (SAND or ROCK).

public:
    /// @brief Default constructor.
    Platform();

    /// @brief Creates a platform at a given position.
    /// @param x X-coordinate of the platform.
    /// @param y Y-coordinate of the platform.
    Platform(int x, int y);
};

#endif // PLATFORM_H