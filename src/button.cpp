#include "../include/button.hpp"

namespace {
    bool checkInside(const sf::Sprite& sprite, const sf::Vector2f& location) {
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
                std::function<void()> action): action(action), info(text) {
    Clicked.setColor(ClickedColor);
    notClicked.setColor(notClickedColor);

    Clicked.setPosition(location);
    notClicked.setPosition(location);

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
    action();
}