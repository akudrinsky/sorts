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

    //~application();

private:
    sf::RenderWindow window;
    sf::Sprite background;
    std::vector<Button> buttons; //sf::Drawable

    bool lostFocus;

    void checkClick(int x_coord, int y_coord);

    sf::Sprite setBackground();
    void setPlots();
    void setButtons();

    friend void MakeApp();
};