#include "../include/graphics.hpp"
#include "../include/statsInt.hpp"

void fun() {
    printf("Quit\n");
}

void MakeApp() {
    application app("data/background.jpg");
    
    Stats bubbleData("./data/BubbleSort.txt");
    Stats qsortData("./data/QSort.txt");

    sf::RectangleShape graphBackground(sf::Vector2f(1000, 600));
    graphBackground.setPosition(sf::Vector2f(100, 200));
    graphBackground.setFillColor(sf::Color::White);

    Graph compares(graphBackground, &bubbleData.sizes, &bubbleData.compares);
    compares.addFunc(&qsortData.compares, sf::Color::Red);

    LOGS("INFO >>> new element of app - compares graph\n")
    app.newElement(compares);

    graphBackground.setPosition(sf::Vector2f(1200, 200));

    Graph swaps(graphBackground, &bubbleData.sizes, &bubbleData.swaps);
    swaps.addFunc(&qsortData.swaps, sf::Color::Red);

    LOGS("INFO >>> new element of app - swaps graph\n")
    app.newElement(swaps);

    LOGS("INFO >>> new button for quit\n")
    app.newButton(
        Button(
            sf::Color(235, 100, 235, 205),
            sf::Color(235, 100, 235, 205),
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

    LOGS("INFO >>> new button for bubble graph\n")
    app.newButton(
        Button(
            sf::Color::Black,
            sf::Color::Black,
            "Bubble",
            "/Library/Fonts/Arial.ttf",
            sf::Vector2f(700, 800), 
            sf::Vector2f(100, 100), 
            [&app]() mutable {
                Graph& graph = app.searchElement(0);
                graph.changeEnable(0);
            }
        )
    );

    LOGS("INFO >>> new button for qsort graph\n")
    app.newButton(
        Button(
            sf::Color::Red,
            sf::Color::Red,
            "Quick",
            "/Library/Fonts/Arial.ttf",
            sf::Vector2f(900, 800), 
            sf::Vector2f(100, 100), 
            [&app]() mutable {
                Graph& graph = app.searchElement(0);
                graph.changeEnable(1);
            }
        )
    );

    LOGS("INFO >>> new button for bubble swaps graph\n")
    app.newButton(
        Button(
            sf::Color::Black,
            sf::Color::Black,
            "Bubble",
            "/Library/Fonts/Arial.ttf",
            sf::Vector2f(1200, 800), 
            sf::Vector2f(100, 100), 
            [&app]() mutable {
                Graph& graph = app.searchElement(1);
                graph.changeEnable(0);
            }
        )
    );

    LOGS("INFO >>> new button for qsort swaps graph\n")
    app.newButton(
        Button(
            sf::Color::Red,
            sf::Color::Red,
            "Quick",
            "/Library/Fonts/Arial.ttf",
            sf::Vector2f(1400, 800), 
            sf::Vector2f(100, 100), 
            [&app]() mutable {
                Graph& graph = app.searchElement(1);
                graph.changeEnable(1);
            }
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

Graph& application::searchElement(int index) {
    if (index >= elems.size()) {
        LOGS("ERROR >>> out of bounds (index is %d, size is only %d)\n", index, elems.size())
    }
    return elems[index];
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

/*
        sf::Font font;
        if (!font.loadFromFile("/Library/Fonts/Arial.ttf")) {
            printf("ERROR >>> no font %s\n", "/Library/Fonts/Arial.ttf");
        }

        sf::Text info("asd\n", font);
        info.setPosition(sf::Vector2f{10, 10});
        info.setColor(sf::Color::Red);
        window.draw(info);
*/
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

void application::newElement(const Graph& elem) {
    elems.push_back(elem);
}

void application::checkClick(int x_coord, int y_coord) {
    for (auto button : buttons) {
        if (button.isInside(sf::Vector2f(x_coord, y_coord))) {
            LOGS("INFO >>> button clicked\n")
            //button.reColor();
            button.performAction();
            break; // NO button beneath another button.
        }
    }
}