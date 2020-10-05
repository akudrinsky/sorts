#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "usefulDefines.hpp"
#include <vector>
#include <limits>
#include <string>
#include <stdexcept>

sf::Font loadFromFile(const char* fontName);

// Implements graph interface for application.
// Is able to contain several functions inside one graph.
class Graph : public sf::Drawable {
public:
    Graph(const sf::RectangleShape& background, 
        std::vector<int>* xCoord, 
        std::vector<int>* yCoord);

    // adds new function to this Graph
    void addFunc(std::vector<int>* newYValues, sf::Color color = sf::Color::Black);

    // this enables functin if that was disabled. Otherwise, disables it. 
    // If out of bounds, throws an exception.
    void enableFunc(int index, bool enable);

    // checks if a function is enabled.
    // If out of bounds, throws an exception.
    bool isEnabled(int index);

    // changes enableness of a given function
    // If out of bounds, throws an exception.
    void changeEnable(int index);

    // changes bounds by ox
    void ChangeBoundsX();

    // If mode is set to true, recounts bounds 
    // every time one of functions is enabled or disabled.
    void alwaysResize(bool mode = false);

    // changes bounds by oy
    void ChangeBoundsY();

private:
    struct func {
        std::vector<int>* vertices;
        sf::Color color;
        bool notForgotten;
    };

    sf::RectangleShape background;
    std::vector<int>* xCoord;
    std::vector<func> yCoord;
    sf::Font font;

    bool resizeAlways;

    int activePointsNum = std::numeric_limits<int>::max();

    double xMax = std::numeric_limits<double>::min(), 
        xMin = std::numeric_limits<double>::max(), 
        yMax = std::numeric_limits<double>::min(), 
        yMin = std::numeric_limits<double>::max();

    void changeBoundsByNew(int index);

    // draws one line of graph
    sf::VertexArray drawOneLine(int nGraph, int nPair) const;

    // sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // draws bounds of a graph
    void drawBoundsNumbers(sf::RenderTarget& target, sf::RenderStates states) const;

    // draws one num in a place location
    void drawNum(double num, const sf::Vector2f& location, sf::RenderTarget& target, sf::RenderStates states) const;
};