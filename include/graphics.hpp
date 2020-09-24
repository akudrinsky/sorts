#pragma once

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "graph.hpp"
#include "usefulDefines.hpp"

#include <vector>

void MakeApp();

class application {
public:
    application(const char* backgroundPath);
    application() = delete;
    NON_COPYBLE(application)

    void eventLoop();

    void newButton(Button&& newButton);
    void setBackground(const char* backgroundPath);
    void newElement(Graph&& elem);

    void Quit();

    //void shutDown();

    //~application();

private:
    sf::RenderWindow window;

    sf::Texture backgroundTexture;
    sf::Sprite background;
    std::vector<Button> buttons;
    std::vector<Graph> elems;

    bool lostFocus;

    void checkClick(int x_coord, int y_coord);

    friend void MakeApp();
};