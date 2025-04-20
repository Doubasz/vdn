#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <functional>
#include "../core/Shapes.h"

class Button {
public:
    enum class State {
        NORMAL,
        HOVER,
        PRESSED,
        DISABLED
    };

    Button();

    Button(int x, int y, int width, int height, const std::string& text,
           SDL_Color normalColor, SDL_Color hoverColor, SDL_Color pressedColor, SDL_Color textColor,
           TTF_Font* font, SDL_Renderer* renderer);
    ~Button();

    Button(Button&& other) noexcept;
    Button& operator=(Button&& other) noexcept;
    
    void updateTextTexture();
    void render();
    void handleEvent(const SDL_Event& e);
    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setText(const std::string& text);
    void setColors(SDL_Color normalColor, SDL_Color hoverColor, SDL_Color pressedColor);
    void setTextColor(SDL_Color textColor);
    void setEnabled(bool enabled);
    void setOnClick(std::function<void()> callback);
    
    bool isEnabled() const { return state != State::DISABLED; }
    bool isPressed() const { return state == State::PRESSED; }
    
private:
   
    Rectangle getRect() const;
    
    Rectangle box;
    std::string text;
    
    SDL_Color normalColor;
    SDL_Color hoverColor;
    SDL_Color pressedColor;
    SDL_Color textColor;
    
    State state;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* textTexture;
    int textWidth, textHeight;
    
    std::function<void()> onClick;
};



#endif // SDL_BUTTON_H
