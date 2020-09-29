#pragma once

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "graph.hpp"
#include "usefulDefines.hpp"

#include <vector>

// Creates application for a program
void MakeApp();

// Basic interface for graphics, consists of buttons and graphs. TODO: more
// TODO: array of pointers to sf::Drawable
class application {
public:
    // backgroundPath - path to background image.
    application(const char* backgroundPath);
    application() = delete;
    NON_COPYBLE(application)

    // checks all events and acts correspondly
    void eventLoop();

    // adds button to this application
    // NOTE: move-semantics only, because only one application for program in assumed
    void newButton(Button&& newButton);

    // sets background
    void setBackground(const char* backgroundPath);

    // adds new element for this app.
    void newElement(const Graph& elem);

    // searches for drawable element in this app.
    Graph& searchElement(int index);

    // quits from application.
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