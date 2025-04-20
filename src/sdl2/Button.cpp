

#include "Button.h"





Button::Button() : text(""), state(State::NORMAL), renderer(nullptr), font(nullptr), textTexture(nullptr),
textWidth(0), textHeight(0), onClick(nullptr){

}

// Implementation
Button::Button(int x, int y, int width, int height, const std::string& text,
    SDL_Color normalColor, SDL_Color hoverColor, SDL_Color pressedColor, SDL_Color textColor,
    TTF_Font* font, SDL_Renderer* renderer)
    :  text(text), normalColor(normalColor), hoverColor(hoverColor), pressedColor(pressedColor), textColor(textColor),
    state(State::NORMAL), renderer(renderer), font(font), textTexture(nullptr),
    textWidth(0), textHeight(0), onClick(nullptr)
{

    box = {x, y, width, height};
    updateTextTexture();
}

Button::~Button() {
    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture);
    }
}




Button::Button(Button&& other) noexcept {
    text = std::move(other.text);
    state = other.state;
    renderer = other.renderer;
    font = other.font;
    textTexture = other.textTexture;
    textWidth = other.textWidth;
    textHeight = other.textHeight;
    onClick = std::move(other.onClick);
    normalColor = other.normalColor;
    hoverColor = other.hoverColor;
    pressedColor = other.pressedColor;
    textColor = other.textColor;
    box = other.box;

    other.textTexture = nullptr; // Prevent double free
}


Button& Button::operator=(Button&& other) noexcept {
    if (this != &other) {
        if (textTexture) SDL_DestroyTexture(textTexture);

        text = std::move(other.text);
        state = other.state;
        renderer = other.renderer;
        font = other.font;
        textTexture = other.textTexture;
        textWidth = other.textWidth;
        textHeight = other.textHeight;
        onClick = std::move(other.onClick);
        normalColor = other.normalColor;
        hoverColor = other.hoverColor;
        pressedColor = other.pressedColor;
        textColor = other.textColor;
        box = other.box;

        other.textTexture = nullptr;
    }
    return *this;
}








void Button::render() {
    Rectangle temp = getRect();
    SDL_Rect buttonRect = {temp.x, temp.y, temp.w, temp.h};

    // Choose color based on state
    SDL_Color currentColor;
    switch (state) {
        case State::HOVER:
        currentColor = hoverColor;
        break;
        case State::PRESSED:
        currentColor = pressedColor;
        break;
        case State::DISABLED:
        // Use a semi-transparent normal color for disabled state
        currentColor = normalColor;
        currentColor.a = 128;
        break;
        case State::NORMAL:
        default:
        currentColor = normalColor;
        break;
    }
    
    // Draw button background
    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
    SDL_RenderFillRect(renderer, &buttonRect);

    // Draw button border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &buttonRect);

    // Draw text if available
    if (textTexture != nullptr) {
        
        SDL_Rect textRect = {
            buttonRect.x + (buttonRect.w - textWidth) / 2,
            buttonRect.y + (buttonRect.h - textHeight) / 2,
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        
    }
}

void Button::handleEvent(const SDL_Event& e) {
    // Ignore events if disabled
    if (state == State::DISABLED) {
        return;
    }

    // Get button rectangle
    Rectangle temp = getRect();
    SDL_Rect buttonRect = {temp.x, temp.y, temp.w, temp.h};

    // Handle different event types
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
    // Get mouse position
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Check if mouse is inside button
    bool inside = (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
                mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h);

    if (!inside) {
        state = State::NORMAL;
    } 
    else{
        switch (e.type) {
            case SDL_MOUSEMOTION:
                state = State::HOVER;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    state = State::PRESSED;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    state = State::HOVER;
                    if (onClick) {
                        onClick();
                    }
                }
                break;
            }
        }
    }
}

void Button::setPosition(int x, int y) {
    box.setX(x);
    box.setY(y);
}

void Button::setSize(int width, int height) {
    box.w = width;
    box.h = height;
}

void Button::setText(const std::string& textT) {
    if (text != textT) {
        text = textT;
        updateTextTexture();
    }
}

void Button::setColors(SDL_Color normalColor, SDL_Color hoverColor, SDL_Color pressedColor) {
    this->normalColor = normalColor;
    this->hoverColor = hoverColor;
    this->pressedColor = pressedColor;
}

void Button::setTextColor(SDL_Color textColorT) {
    if (textColor.r != textColorT.r || textColor.g != textColorT.g || 
        textColor.b != textColorT.b || textColor.a != textColorT.a) {
        textColor = textColorT;
        updateTextTexture();
    }
}

void Button::setEnabled(bool enabled) {
    state = enabled ? State::NORMAL : State::DISABLED;
}

void Button::setOnClick(std::function<void()> callback) {
    onClick = callback;
}

void Button::updateTextTexture() {
    // Clean up old texture
    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }

    // Create new texture if we have text and a font
    if (!text.empty() && font != nullptr) {
                
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
        if (textSurface != nullptr) {

            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            int originalW = textSurface->w;
            int originalH = textSurface->h;

            int padding = 25;
            int maxW = box.w - 2 * padding;
            int maxH = box.h - 2 * padding;

            float scaleW = (float)maxW / originalW;
            float scaleH = (float)maxH / originalH;
            float scale = std::min(scaleW, scaleH);  // maintain aspect ratio


            textWidth = (int)(originalW * scale);
            textHeight = (int)(originalH * scale);

            SDL_SetTextureBlendMode(textTexture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(textTexture, 255);

            SDL_FreeSurface(textSurface);
        }
    }
}

Rectangle Button::getRect() const {
    return box;
}

