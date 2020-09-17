#pragma once

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "usefulDefines.hpp"

#include <vector>

void MakeApp();

class application {
public:
    application(const char* backgroundPath);
    application() = delete;
    NON_COPYBLE(application)

    void eventLoop();

    //void shutDown();

    //~application();

private:
    sf::RenderWindow window;

    sf::Texture backgroundTexture;
    sf::Sprite background;
    std::vector<Button> buttons;


    bool lostFocus;

    void checkClick(int x_coord, int y_coord);

    void setBackground(const char* backgroundPath);
    void setPlots();
    void newButton(const Button& newButton);

    friend void MakeApp();
};