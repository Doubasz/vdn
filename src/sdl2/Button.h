#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <functional>
#include "../core/Shapes.h"

/// A button class to represent an interactive button with SDL2
///
/// This class provides functionality for creating, rendering,
/// and interacting with a button in a graphical user interface.
/// It supports multiple states (normal, hover, pressed, disabled),
/// customizable colors, and can handle click events through a callback.
///
/// @note The button uses a rectangle (`Rectangle`) for its positioning
///       and a text (`std::string`) for its label, with support for
///       font rendering using SDL_ttf.
class Button {
public:
    /// Enum representing the possible states of the button
    ///
    /// - NORMAL: The button in its default state.
    /// - HOVER: The button when the mouse hovers over it.
    /// - PRESSED: The button when it is clicked.
    /// - DISABLED: The button is disabled and unclickable.
    enum class State {
        NORMAL,     ///< Default state
        HOVER,      ///< Hovered state
        PRESSED,    ///< Clicked state
        DISABLED    ///< Disabled state (unclickable)
    };

    /// Default constructor to create an empty button
    Button();

    /// Parameterized constructor to create a button with custom attributes
    ///
    /// @param x, y The position of the button (top-left corner)
    /// @param width, height The dimensions of the button
    /// @param text The label text displayed on the button
    /// @param normalColor, hoverColor, pressedColor The button's colors in different states
    /// @param textColor The color of the text displayed on the button
    /// @param font The font used for rendering the text
    /// @param renderer The SDL_Renderer for rendering the button and text
    Button(int x, int y, int width, int height, const std::string& text,
           SDL_Color normalColor, SDL_Color hoverColor, SDL_Color pressedColor, SDL_Color textColor,
           TTF_Font* font, SDL_Renderer* renderer);

    /// Destructor to clean up resources (like textures)
    ~Button();

    /// Move constructor for transferring ownership of the button resources
    Button(Button&& other) noexcept;

    /// Move assignment operator for transferring ownership of the button resources
    Button& operator=(Button&& other) noexcept;
    
    /// Updates the button's text texture, re-rendering if needed
    void updateTextTexture();

    /// Renders the button (background and text) to the screen
    void render();

    /// Handles input events such as mouse hover and clicks
    ///
    /// @param e The SDL_Event to process
    void handleEvent(const SDL_Event& e);

    /// Sets the position of the button
    ///
    /// @param x, y The new position (top-left corner)
    void setPosition(int x, int y);

    /// Sets the size of the button
    ///
    /// @param width, height The new dimensions of the button
    void setSize(int width, int height);

    /// Gets the current text of the button
    ///
    /// @return The current text label of the button
    std::string getText() const;

    /// Gets the current state of the button
    ///
    /// @return The current button state (NORMAL, HOVER, PRESSED, DISABLED)
    State getState() const;

    /// Gets the normal color of the button (used in the default state)
    ///
    /// @return The normal color of the button
    SDL_Color getNormalColor() const;

    /// Sets the text of the button
    ///
    /// @param text The new text to display on the button
    void setText(const std::string &text);

    /// Sets the colors of the button in different states
    ///
    /// @param normalColor, hoverColor, pressedColor The colors for each state
    void setColors(SDL_Color normalColor, SDL_Color hoverColor, SDL_Color pressedColor);

    /// Sets the color of the text on the button
    ///
    /// @param textColor The color of the button's text
    void setTextColor(SDL_Color textColor);

    /// Enables or disables the button
    ///
    /// @param enabled If true, the button is enabled; otherwise, it's disabled
    void setEnabled(bool enabled);

    /// Sets the callback function to be called when the button is clicked
    ///
    /// @param callback The function to be called when the button is clicked
    void setOnClick(std::function<void()> callback);
    
    /// Checks if the button is enabled
    ///
    /// @return true if the button is enabled, false if it's disabled
    bool isEnabled() const { return state != State::DISABLED; }

    /// Checks if the button is pressed
    ///
    /// @return true if the button is in the PRESSED state
    bool isPressed() const { return state == State::PRESSED; }

    /// Gets the button's rectangle (used for positioning and collision detection)
    ///
    /// @return A `Rectangle` representing the button's area
    Rectangle getRect() const;

private:
    Rectangle box; ///< The rectangle representing the button's area
    std::string text; ///< The text displayed on the button
    
    SDL_Color normalColor; ///< Color for the normal state
    SDL_Color hoverColor; ///< Color for the hover state
    SDL_Color pressedColor; ///< Color for the pressed state
    SDL_Color textColor; ///< Color of the text on the button
    
    State state; ///< The current state of the button
    SDL_Renderer* renderer; ///< The SDL renderer for rendering the button
    TTF_Font* font; ///< The font used for rendering the button's text
    SDL_Texture* textTexture; ///< The texture for the button's text
    int textWidth, textHeight; ///< Dimensions of the text texture
    
    std::function<void()> onClick; ///< The callback function for click events
};

#endif // SDL_BUTTON_H
