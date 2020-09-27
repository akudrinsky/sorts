//#include "../include/graphics.hpp"
#include "../include/button.hpp"

namespace {
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

Button::Button(const sf::Color& notClickedColor, 
                const sf::Color& ClickedColor, 
                const char* text,
                const char* fontName, 
                const sf::Vector2f& location, 
                const sf::Vector2f& size, 
                const std::function<void(void)>& action): action(action) {
    Clicked.setFillColor(ClickedColor);
    notClicked.setFillColor(notClickedColor);

    Clicked.setPosition(location);
    notClicked.setPosition(location);

    Clicked.setSize(size);
    notClicked.setSize(size);

    if (!font.loadFromFile(fontName)) {
        LOGS("ERROR >>> no font %s\n", fontName)
    }

    info = sf::Text(text, font, 40);
    //info.setCharacterSize(40); // TODO - more flexibility.
    info.setColor(sf::Color::Red);

    info.setPosition(sf::Vector2f{10, 10});

    /*
    const sf::FloatRect bounds(info.getLocalBounds());
    const sf::Vector2f box(size);
    info.setOrigin(bounds.width / 2.0f + bounds.left, 
                    bounds.height / 2.0f + bounds.top);
    info.setPosition(location);
    */
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
    
    target.draw(info, states);
}

void Button::performAction() {
    LOGS("INFO >>> %p button was clicked on\n", this)
    action();
}