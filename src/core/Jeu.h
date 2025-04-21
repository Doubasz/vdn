#ifndef JEU_H
#define JEU_H

#include <vector>
#include <iostream>
#include "Level.h"

/// Enum representing the different states the game can be in.
enum State {
    MENU_PRINCIPAL,  ///< Main menu
    CHOIX_NIVEAU,    ///< Level selection screen
    NIVEAU,          ///< Gameplay in a level
    MENU_NIVEAU      ///< In-level pause menu
};

/// @class Jeu
/// @brief Handles the main game logic and state transitions.
///
/// This class contains the current level and manages the overall game state.
class Jeu {

    Level currentLevel;  ///< The currently loaded level
    int state;            ///< Current game state (see State enum)

public:

    /// @brief Constructor
    Jeu();

    /// @brief Starts the main game loop.
    void gameLoop();

    /// @brief Gets the current state of the game.
    /// @return Current game state.
    int getState() const;

    /// @brief Sets the current state of the game.
    /// @param newState The new state to set.
    void setState(int newState);

    /// @brief Loads the specified level.
    /// @param level The level number to load.
    void loadLevel(int level);

    /// @brief Gets the current level object.
    /// @return Reference to the current Level.
    Level& getCurrentLevel();

    /// @brief Updates the current level based on player input and elapsed time.
    /// @param input The current input string.
    /// @param deltaTime Time elapsed since last frame (in seconds).
    void update(std::string input, float deltaTime);
};

#endif // JEU_H
