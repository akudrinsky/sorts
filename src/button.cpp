#include "../include/button.hpp"

namespace {
    // local (for button.cpp) function to check if location is inside area.
    bool checkInside(const sf::RectangleShape& area, const sf::Vector2f& location) {
        LOGS("INFO >>> checkInside\n")
        if (location.x >= area.getPosition().x and 
            location.x <= area.getPosition().x + area.getGlobalBounds().width and
            location.y >= area.getPosition().y and
            location.y <= area.getPosition().y + area.getGlobalBounds().height) {

            return true;
        }
        return false;
    }
}

sf::Font loadFromFile(const char* fontName) {
    sf::Font font;
    if (!font.loadFromFile(fontName)) {
        LOGS("ERROR >>> no font %s\n", fontName)
    }
    return font;
}

Button::Button(const sf::Color& notClickedColor, 
                const sf::Color& ClickedColor, 
                const sf::String& text,
                const char* fontName, 
                const sf::Vector2f& location, 
                const sf::Vector2f& size, 
                const std::function<void(void)>& action) 
                :
                action(action),
                font(loadFromFile(fontName)),
                text(text),
                textColor(sf::Color::White) {

    Clicked.setFillColor(ClickedColor);
    notClicked.setFillColor(notClickedColor);

    Clicked.setPosition(location);
    notClicked.setPosition(location);

    Clicked.setSize(size);
    notClicked.setSize(size);
    // TODO: resize
}

bool Button::isInside(const sf::Vector2f& location) {
    if (isClicked) {
        return checkInside(Clicked, location);
    }
    else {
        return checkInside(notClicked, location);
    }
}

void Button::reColor() {
    isClicked = !isClicked;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isClicked) {
        target.draw(Clicked, states);
    }
    else {
        target.draw(notClicked, states);
    }
    
    sf::Text info(text, font);

    info.setColor(textColor);

    auto size = Clicked.getSize();
    auto location = Clicked.getPosition();
    location.x += size.x / 2.0f;
    location.y += size.y / 2.0f;

    const sf::FloatRect bounds(info.getLocalBounds());
    info.setOrigin(bounds.width / 2.0f + bounds.left, 
                    bounds.height / 2.0f + bounds.top);
    info.setPosition(location);

    target.draw(info, states);
}

void Button::colorText(const sf::Color& newColor) {
    textColor = newColor;
}

void Button::performAction() {
    LOGS("INFO >>> %p button was clicked on\n", this)
    action();
}