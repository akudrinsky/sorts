#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "usefulDefines.hpp"

class Button : public sf::Drawable {
public:
    Button(const sf::Color& notClickedColor, 
            const sf::Color& ClickedColor, 
            const char* text, 
            const char* fontName,
            const sf::Vector2f& location, 
            const sf::Vector2f& size, 
            const std::function<void(void)>& action);

    //~Button();
    bool isInside(const sf::Vector2f& location);
    void reColor();
    void performAction();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::function<void(void)> action;

    sf::RectangleShape Clicked;
    sf::RectangleShape notClicked;

    sf::Font font;
    sf::Text info;

    bool isClicked;
};