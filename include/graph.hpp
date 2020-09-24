#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "usefulDefines.hpp"
#include <vector>
#include <limits>

class Graph : public sf::Drawable {
public:
    Graph(const sf::RectangleShape& background, 
        std::vector<int>& xCoord, 
        std::vector<int>& yCoord, 
        const sf::Vector2f& size);

    void ChangeBoundsX();
    void ChangeBoundsY();

private: 
    sf::RectangleShape background;
    sf::Vector2f size;
    std::vector<int>& xCoord;
    std::vector<int>& yCoord;

    double xMax = std::numeric_limits<double>::min(), 
        xMin = std::numeric_limits<double>::max(), 
        yMax = std::numeric_limits<double>::min(), 
        yMin = std::numeric_limits<double>::max();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};