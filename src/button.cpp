#include "../include/button.hpp"

namespace {
    bool checkInside(const sf::RectangleShape& sprite, const sf::Vector2f& location) {
        if (location.x >= sprite.getPosition().x and 
            location.x <= sprite.getPosition().x + sprite.getGlobalBounds().width and
            location.y >= sprite.getPosition().y and
            location.y <= sprite.getPosition().y + sprite.getGlobalBounds().height) {

            return true;
        }
        return false;
    }
}


Button::Button(const sf::Color& notClickedColor, 
                const sf::Color& ClickedColor, 
                const sf::String& text, 
                const sf::Vector2f& location, 
                const sf::Vector2f& size): info(text) {
    Clicked.setFillColor(ClickedColor);
    notClicked.setFillColor(notClickedColor);

    Clicked.setPosition(location);
    notClicked.setPosition(location);

    Clicked.setSize(size);
    notClicked.setSize(size);

    //notClicked.setScale(100, 100);
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
}

void Button::performAction() {
    LOGS("INFO >>> %p button was clicked on\n", this)
    action();
}