#include "../include/graphics.hpp"
#include "../include/statsInt.hpp"

void fun() {
    printf("Quit\n");
}

void MakeApp() {
    application app("data/background.jpg");
    
    app.newButton(
        Button(
            sf::Color(235, 100, 235, 255),
            sf::Color(235, 100, 235, 255),
            "Quit",
            "/Library/Fonts/Arial.ttf",
            sf::Vector2f(500, 800), 
            sf::Vector2f(100, 100), 
            [&app]() mutable {
                printf("Quitting app\n");
                app.Quit();
            }
        )
    );

    Stats bubbleData("./data/BubbleSort.txt");
    sf::RectangleShape graphBackground(sf::Vector2f(600, 600));
    graphBackground.setFillColor(sf::Color::White);
    app.newElement(
        Graph(
            graphBackground,
            bubbleData.sizes,
            bubbleData.compares,
            sf::Vector2f(200, 100)
        )
    );
    
    app.eventLoop();
}

application::application(const char* backgroundPath): window(sf::VideoMode::getDesktopMode(), "Sort algorithms"), 
                                lostFocus(false) {
    setBackground(backgroundPath);
}

void application::Quit() {
    window.close();
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
                        LOGS("INFO >>> Focus was lost\n");
                    }
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    LOGS("INFO >>> there was a click at (%d, %d)\n", event.mouseButton.x, event.mouseButton.y)
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
            //LOGS("INFO >>> drawing button\n")
            window.draw(button);
        }

        for (auto elem : elems) {
            window.draw(elem);
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

void application::newButton(Button&& newButton) {
    //newButton.setApp(*this);
    buttons.push_back(std::forward<Button&&>(newButton));
}

void application::newElement(Graph&& elem) {
    elems.push_back(elem);
}

void application::checkClick(int x_coord, int y_coord) {
    for (auto button : buttons) {
        if (button.isInside(sf::Vector2f(x_coord, y_coord))) {
            LOGS("INFO >>> button clicked\n")
            button.reColor();
            button.performAction();
            break; // NO button beneath another button.
        }
    }
}