#include "../include/graphics.hpp"

void MakeApp() {
    application app;
    app.setButtons();

    app.eventLoop();
}

application::application(): window(sf::VideoMode::getDesktopMode(), "Sort algorithms"), 
                                background(setBackground()), 
                                lostFocus(false) {
    
}

void application::eventLoop() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed: {
                window.close();
                break;
            }
            case sf::Event::LostFocus: {
                lostFocus = true;
                break;
            }
            case sf::Event::GainedFocus: {
                if (lostFocus) {
                    printf("Focus was lost\n");
                }
                break;
            }
            case sf::Event::MouseButtonPressed: {
                checkClick(event.mouseButton.x, event.mouseButton.y);
                break;
            }
            default:
                break;
            };
        }

        //window.clear();
        window.draw(background);
        window.display();
    }
}



sf::Sprite application::setBackground() {
    sf::Texture texture;
    texture.loadFromFile("data/background.jpg");

    sf::Sprite spite(texture);
    spite.setScale(window.getSize().x, window.getSize().y);
    //spite.scale(window.getSize().x / spite.getLocalBounds().width, window.getSize().y / spite.getLocalBounds().height);
    return spite;
}

void application::setButtons() {
    
}

void application::checkClick(int x_coord, int y_coord) {
    for (auto button : buttons) {
        if (button.isInside(sf::Vector2f(x_coord, y_coord))) {
            button.reColor();
            button.performAction();
            LOGS("INFO >>> button clicked: %s\n", button.info())
            break; // NO button beneath another button.
        }
    }
}