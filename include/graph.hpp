#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "usefulDefines.hpp"
#include <vector>
#include <limits>

// Implements graph interface for application.
// Is able to contain several functions inside one graph.
class Graph : public sf::Drawable {
public:
    Graph(const sf::RectangleShape& background, 
        std::vector<int>* xCoord, 
        std::vector<int>* yCoord);

    // adds new function to this Graph
    void addFunc(std::vector<int>* newYValues, sf::Color color = sf::Color::Black);

    void enableFunc(int index, bool enable);

    bool isEnabled(int index);

    void changeEnable(int index);

    void ChangeBoundsX();
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

    int activePointsNum = std::numeric_limits<int>::max();

    double xMax = std::numeric_limits<double>::min(), 
        xMin = std::numeric_limits<double>::max(), 
        yMax = std::numeric_limits<double>::min(), 
        yMin = std::numeric_limits<double>::max();

    void changeBoundsByNew(int index);

    sf::VertexArray drawOneLine(int nGraph, int nPair) const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};