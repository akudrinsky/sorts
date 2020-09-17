#include "../include/graphics.hpp"

void fun() {
    printf("Quit\n");
}

void MakeApp() {
    application app("data/background.jpg");
    
    app.newButton(
        Button(
            sf::Color(235, 100, 235, 100),
            sf::Color(100, 235, 100, 100),
            "Quit",
            sf::Vector2f(10, 10)
        )
    );
    
    app.eventLoop();
}

application::application(const char* backgroundPath): window(sf::VideoMode::getDesktopMode(), "Sort algorithms"), 
                                lostFocus(false) {
    setBackground(backgroundPath);
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

        window.clear();
        window.draw(background);
        for (auto button : buttons) {
            window.draw(button);
        }
        window.display();
    }
}

void application::setBackground(const char* backgroundPath) {
    backgroundTexture.loadFromFile(backgroundPath);

    background = sf::Sprite (backgroundTexture);
    //background.setScale(window.getSize().x, window.getSize().y);
    background.scale(window.getSize().x / background.getLocalBounds().width, window.getSize().y / background.getLocalBounds().height);
}

void application::newButton(const Button& newButton) {
    buttons.push_back(newButton);
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