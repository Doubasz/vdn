#ifndef IN_GAME_STATE_H
#define IN_GAME_STATE_H

#include <SDL2/SDL_mixer.h>
#include "GameState.h"
#include <SDL2/SDL_image.h>
#include "../core/Jeu.h"
#include "../core/Camera.h"
#include "Button.h"

#define SCREEN_WIDTH 1400  ///< The width of the game screen
#define SCREEN_HEIGHT 900 ///< The height of the game screen

/// Enum representing the possible states of the game window
///
/// - CONTINUE: The game is running normally
/// - PAUSE: The game is paused
/// - QUIT: The game is quitting
/// - DEAD: The player is dead
enum WindowState{
    CONTINUE, PAUSE, QUIT, END,DEAD
};

/// A structure to represent an animation for an object (like the player or enemies)
///
/// - startFrame: The index of the first frame of the animation
/// - numFrames: The total number of frames in the animation
/// - currentFrame: The index of the current frame
/// - frameTime: The time duration for each frame in seconds
/// - timer: A timer to track the elapsed time for frame switching
/// - loop: If true, the animation loops back to the first frame after finishing
struct Animation{
    int startFrame;    ///< The first frame of the animation
    int numFrames;     ///< The total number of frames in the animation
    int currentFrame;  ///< The index of the current frame
    float frameTime;   ///< The time each frame should be displayed for
    float timer;       ///< Timer for controlling the animation frame switch
    bool loop;         ///< Whether the animation should loop after completion
};

/// The class representing the in-game state, including all game logic, rendering, and interactions
/// It manages the game state during gameplay, including level rendering, player and enemy animations,
/// sounds, and the user interface like buttons and health status.
class InGameState : public GameState{

private:
    SDL_Renderer* renderer;    ///< The SDL renderer used for drawing everything to the screen
    int level;                 ///< The current game level
    Jeu jeu;                   ///< The game logic (model) that contains the game state

    SDL_Texture* background;       ///< The background texture
    SDL_Texture* background1;      ///< An alternative background texture
    SDL_Texture* tileSet;          ///< The texture for the game's tiles

    SDL_Texture* deathBackground;  ///< The background for the death screen

    SDL_Texture* playerSheet;      ///< The texture sheet for the player sprite
    SDL_Rect playerRect;           ///< The rectangle for positioning the player sprite

    std::vector<Animation> playerAnimation; ///< The list of animations for the player
    Animation currentAnimation;    ///< The current animation being played for the player

    std::vector<SDL_Texture*> platformTexture; ///< The textures for the platforms
    std::vector<Button> buttons;            ///< The buttons used in the game (pause, resume, etc.)

    SDL_Texture* ennemySheet;       ///< The texture sheet for the enemy sprite
    TTF_Font* font;                 ///< The font for rendering text (e.g., for score)
    SDL_Color textColor;            ///< The color for rendering text

    Animation ennemyAnimation;      ///< The animation for the enemies

    Camera camera;                  ///< The camera to control the visible game area

    // Sound effects and music
    Mix_Chunk* sauter;      ///< Sound for jumping
    Mix_Chunk* gotHit;      ///< Sound for player taking damage
    Mix_Chunk* walk;        ///< Sound for player walking
    Mix_Chunk* attack;      ///< Sound for player attacking
    Mix_Chunk* land;        ///< Sound for player landing
    Mix_Music* music;       ///< Background music for the game

    Timer moveTimer;         ///< Timer for controlling movement events
    Timer attacksound;       ///< Timer for controlling attack sound events

    int tileSize;            ///< The size of each tile
    int state;               ///< The current game state (e.g., playing, paused)
    int blinkInterval;       ///< Interval for blinking effects (e.g., when player is invincible)
    int lastPlayerState;     ///< Stores the last state of the player (e.g., alive, dead)
    bool quit;               ///< Flag to indicate whether the game should quit

    float deathDuration;     ///< Duration of the death screen
    float deathTimer;        ///< Timer for controlling death screen display time

    int gameTime;            ///< The current game time (used for timing and events)

public:
    // Constructors and destructors

    /// Default constructor for the in-game state
    InGameState();

    /// Parameterized constructor to initialize the in-game state with custom values
    ///
    /// @param renderer The SDL renderer to be used for rendering
    /// @param font The font for rendering text (e.g., score, timer)
    /// @param lvl The level of the game to start at
    InGameState(SDL_Renderer* renderer, TTF_Font* font, int lvl);

    /// Loads the game resources like textures and sounds
    void load() override;

    /// Gets the tileset texture used for drawing the game's world
    ///
    /// @return The tileset texture
    SDL_Texture *getTileSet() const;

    /// Unloads all resources and prepares the game for a new state
    ///
    /// @return An integer indicating the status of the unloading
    int unload() override;

    /// Handles events like player input or system events
    ///
    /// @param events The SDL event to be handled
    void handleEvents(SDL_Event& events) override;
    void renderGameOverScreen(SDL_Renderer *renderer);
   
    StateCode update(float dt) override;

    /// Renders the game to the screen
    ///
    /// @param renderer The SDL renderer to render the game
    void render(SDL_Renderer* renderer) override;

    // Helper rendering functions for different game elements

    void renderPlayer(SDL_Renderer* renderer);     ///< Renders the player on the screen
    void renderEnnemy(SDL_Renderer* renderer);     ///< Renders the enemy on the screen
    void renderTiles(SDL_Renderer* renderer);      ///< Renders the game tiles on the screen
    void renderBackground(SDL_Renderer* renderer);///< Renders the background of the game
    void renderLives(SDL_Renderer* renderer);      ///< Renders the player's remaining lives
    void renderTimer(SDL_Renderer* renderer);      ///< Renders the game timer
    void renderDeathScreen(SDL_Renderer* renderer);///< Renders the death screen when the player dies

    /// Loads the game textures (player, enemies, backgrounds, etc.)
    void loadTextures(SDL_Renderer* renderer);

    /// Retrieves the background texture for the game
    SDL_Texture *getBackground() const;

    /// Retrieves the player sprite sheet texture
    SDL_Texture *getPlayerSheet() const;

    /// Retrieves the enemy sprite sheet texture
    SDL_Texture *getEnnemySheet() const;

    /// Retrieves the secondary background texture
    SDL_Texture *getBackground1() const;

    /// Retrieves the list of player animations
    const std::vector<Animation> &getPlayerAnimation() const;

    /// Loads animations for the player and enemies
    void loadAnimations();

    /// Updates the game logic such as player movement, collisions, etc.
    void updateGame(float deltaTime);

    /// Updates the player's animation based on elapsed time
    void updateAnimation(float deltaTime);

    /// Updates the enemy's animation based on elapsed time
    void updateEnnemyAnimation(float deltaTime);

    /// Updates the camera's position and view
    void updateCamera(float deltaTime);

    /// Updates the death screen logic, if the player is dead
    void updateDeath(float delatTime);

    /// Plays the background music for the game
    int playBackgroundMusic();

    /// Plays a specific sound effect based on the input string
    ///
    /// @param input The name of the sound to be played
    void playSound(std::string input);

    /// Loads all the sound resources based on the current level
    int loadSounds(int niveau);

    /// Initializes the game buttons (pause, resume, etc.)
    void initButtons();

    /// Resumes the game from a paused state
    void resumeGame();

    /// Quits the game, triggering the end of the game loop
    void quitGame();

    /// Renders the buttons on the screen (e.g., pause, resume)
    void renderButtons();
};

// Loads a texture from a file path
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);

#endif // IN_GAME_STATE_H