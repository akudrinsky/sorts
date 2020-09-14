#pragma once

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "usefulDefines.hpp"

#include <vector>

void MakeApp();

class application {
public:
    application();

    void eventLoop();

    //void shutDown();

    //~application();

private:
    sf::RenderWindow window;
    sf::Sprite background;
    std::vector<Button> buttons;

    bool lostFocus;

    void checkClick(int x_coord, int y_coord);

    sf::Sprite setBackground();
    void setPlots();
    void newButton(const Button& newButton);

    friend void MakeApp();
};