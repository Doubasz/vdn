#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <cassert>

/// MenuState is the class that represents the main menu of the game.
/// It manages the display of the menu, buttons, background, music, and user interactions.
class MenuState : public GameState {

    /// Enum to represent the possible states of the menu screen
    ///
    /// - NORMAL: The normal menu view.
    /// - LEVELS: A menu view that allows the player to choose the level.
    /// - OPTION: A menu view for game options like settings.
    enum WindowStat{
        NORMAL, ///< The normal menu state
        LEVELS, ///< The level selection state
        OPTION  ///< The options (settings) state
    };

private:
    SDL_Renderer* renderer;  ///< The SDL renderer used for rendering game elements
    TTF_Font* font;          ///< The font used for rendering text in the menu

    SDL_Texture* background; ///< The background texture for the menu
    std::vector<Button> buttons; ///< A list of buttons in the menu (e.g., Start, Options)
    std::vector<Button> lvlButtons; ///< A list of level selection buttons

    Mix_Music* music;        ///< The background music for the menu

    GameState::StateCode whatToDoNow; ///< The next game state after the menu (e.g., go to the game, options)
    int state;                ///< The current state of the menu (NORMAL, LEVELS, OPTION)

public:
    /// Default constructor
    MenuState();

    /// Constructor with parameters to initialize the renderer and font
    ///
    /// @param renderer The SDL renderer used for drawing
    /// @param font The font used for rendering text in the menu
    MenuState(SDL_Renderer* renderer, TTF_Font* font);

    /// Destructor to free allocated resources
    ~MenuState();

    /// Loads the resources for the menu (e.g., textures, sounds)
    void load() override;

    /// Unloads resources when exiting the menu
    ///
    /// @return An integer indicating the unloading status
    int unload() override;

    /// Handles user input and events like button clicks or key presses
    ///
    /// @param events The SDL event to be handled (user input)
    void handleEvents(SDL_Event& events) override;

    /// Updates the menu state based on elapsed time and interactions
    ///
    /// @param dt The delta time (time elapsed since the last update)
    /// @return The next state code (e.g., Game, Options)
    StateCode update(float dt) override;

    /// Renders the menu to the screen
    ///
    /// @param renderer The SDL renderer used to draw the menu
    void render(SDL_Renderer* renderer) override;

    // Helper functions to handle menu items

    /// Initializes the menu buttons (Start, Options, etc.)
    void initButtons();

    /// Renders the background image of the menu
    ///
    /// @param renderer The SDL renderer used to render the background
    void renderBackground(SDL_Renderer* renderer);

    /// Loads the background music for the menu
    void load_music();

    /// Plays the background music
    ///
    /// @return An integer indicating the music playback status
    int playBackgroundMusic();

    /// Renders the general buttons in the menu (e.g., Start, Options)
    void renderButtons();

    /// Renders the buttons for level selection
    void renderLevelButtons();

    /// Loads textures used in the menu (e.g., buttons, background)
    void loadTextures();

    // Button actions (menu navigation)

    /// Starts the game (switch to the game state)
    void startGame();

    /// Switches to the level selection screen
    void chooseLevel();

    /// Switches to the options screen
    void options();

    /// Starts the first level of the game
    void startLevel1();

    /// Starts the second level of the game
    void startLevel2();
};

// Loads a texture from a file path for the menu
SDL_Texture* loadTextureM(SDL_Renderer* renderer, const char* path);

#endif // MENU_STATE_H
