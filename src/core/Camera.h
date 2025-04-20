#ifndef CAMERA_H
#define CAMERA_H

#include <algorithm>

/// @brief Handles camera positioning and effects (like shake) in a 2D game.
/// 
/// The camera follows a target entity (typically the player) within the level boundaries.
/// It takes the center of the player and follows it
///
/// Supports smooth following and screen shake effects for immersive gameplay.
///
/// TODO Might add a dead zone to see if it looks better
class Camera {

public:
    float x, y;        ///< Current camera position (top-left corner).
    int w, h;          ///< Viewport dimensions.

    float targetX, targetY;  ///< Target position for the camera to follow.

    bool smoothFollow;       ///< Enables smooth camera movement.
    float followSpeed;       ///< Speed of smoothing (only if smoothFollow is true).

    bool isShaking;          ///< Indicates whether the camera is currently shaking.
    float shakeDuration;     ///< Total duration of the shake effect.
    float shakeTimer;        ///< Timer tracking elapsed shake time.
    float shakeIntensity;    ///< Intensity (amplitude) of the shake.

    int levelWidth, levelHeight; ///< Total dimensions of the level (to constrain camera).

    /// @brief Default constructor.
    /// Initializes all values to zero or defaults.
    Camera() : x(0), y(0), w(0), h(0) {}

    /// @brief Constructs a camera with given viewport and level dimensions.
    /// @param w Width of the viewport.
    /// @param h Height of the viewport.
    /// @param mapWidth Total width of the level.
    /// @param mapHeight Total height of the level.
    Camera(int w, int h, int mapWidth, int mapHeight)
        : x(0), y(0), targetX(0), targetY(0),
          w(w), h(h),
          smoothFollow(false), followSpeed(5.0f),
          levelWidth(mapWidth), levelHeight(mapHeight) {}

    /// @brief Updates the camera position based on a target.
    /// @param targetX X-coordinate of the target to follow.
    /// @param targetY Y-coordinate of the target to follow.
    /// @param deltaTime Time elapsed since the last update (for smooth movement).
    void update(float targetX, float targetY, float deltaTime);

    /// @brief Starts a camera shake effect.
    /// @param intensity How much the screen should shake.
    /// @param duration How long the shake should last.
    void shake(float intensity, float duration);

    /// @return Current X position of the camera.
    float getX() const { return x; }

    /// @return Current Y position of the camera.
    float getY() const { return y; }

    /// @brief Enables or disables smooth camera following.
    /// @param smooth If true, camera will ease toward target position.
    void setSmoothFollow(bool smooth) { smoothFollow = smooth; }

    /// @brief Sets the smoothing speed for smooth follow.
    /// @param s New follow speed.
    void setFollowSpeed(float s) { followSpeed = s; }

    /// @brief Defines the level's boundaries for camera constraint.
    /// @param w Width of the level.
    /// @param h Height of the level.
    void setLevelBoundaries(int w, int h) { levelWidth = w; levelHeight = h; }

};

#endif // CAMERA_H