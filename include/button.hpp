#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "usefulDefines.hpp"
#include <string>

// Implements button interface for application.
class Button : public sf::Drawable {
public:
    // Basic constructor. TODO: make it more flexible.
    Button(const sf::Color& notClickedColor, 
            const sf::Color& ClickedColor, 
            const sf::String& text, 
            const char* fontName,
            const sf::Vector2f& location, 
            const sf::Vector2f& size, 
            const std::function<void(void)>& action);

    //~Button();

    // Checks if click was inside the button
    bool isInside(const sf::Vector2f& location);

    // Recolors button. TODO: make it work
    void reColor();
    
    // Performs action, which was associated with the button.
    void performAction();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::function<void(void)> action;

    sf::RectangleShape Clicked;
    sf::RectangleShape notClicked;

    sf::String text;
    sf::Font font;
    //sf::Text info;

    bool isClicked;
};