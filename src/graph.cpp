#include "../include/graph.hpp"

Graph::Graph(const sf::RectangleShape& background, 
                std::vector<int>& xCoord, 
                std::vector<int>& yCoord, 
                const sf::Vector2f& size) :
                background(background), 
                xCoord(xCoord), 
                yCoord(yCoord), 
                size(size) {
    ChangeBoundsX();
    ChangeBoundsY();
}

void Graph::ChangeBoundsX() {
    for (auto elem : xCoord) {
        if (elem < xMin) {
            xMin = elem;
        }

        if (elem > xMax) {
            xMax = elem;
        }
    }
}

void Graph::ChangeBoundsY() {
    for (auto elem : yCoord) {
        if (elem < yMin) {
            yMin = elem;
        }

        if (elem > yMax) {
            yMax = elem;
        }
    }
}
    
void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    int nPoints = std::min(xCoord.size(), yCoord.size());
    target.draw(background);

    if (nPoints == 1) {
        return;
    }

    sf::FloatRect place = background.getGlobalBounds();

    for (int i = 1; i < nPoints; ++i) {
        sf::VertexArray line (sf::Lines, 2);
        
        line[0].position = sf::Vector2f(
            place.left + xCoord[i], 
            place.top + yCoord[i]
        );
        line[1].position = sf::Vector2f(
            place.left + xCoord[i - 1], 
            place.top + yCoord[i - 1]
        );
        
        line[0].color = sf::Color::Black;
        line[1].color = sf::Color::Black;

        //LOGS("INFO >>> line (%d, %d) -> (%d, %d) needs to be drawn\n", xCoord[i], yCoord[i], xCoord[i - 1], yCoord[i - 1])

        target.draw(line);
    }
}