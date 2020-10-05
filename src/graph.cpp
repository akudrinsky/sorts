#include "../include/graph.hpp"

Graph::Graph(const sf::RectangleShape& background, 
                std::vector<int>* xCoord, 
                std::vector<int>* initYCoord) 
                :
                background(background), 
                xCoord(xCoord) {

    ChangeBoundsX();
    addFunc(initYCoord);
}

void Graph::addFunc(std::vector<int>* newYValues, sf::Color color) {
    yCoord.push_back({newYValues, color, true});
    changeBoundsByNew(yCoord.size() - 1);
    LOGS("INFO >>> new %d'th function of graph %p!\n", yCoord.size() - 1, this)
}

void Graph::ChangeBoundsX() {
    if (activePointsNum > xCoord->size()) {
        activePointsNum = xCoord->size();
    }
    for (auto elem : *xCoord) {
        if (elem < xMin) {
            xMin = elem;
        }

        if (elem > xMax) {
            xMax = elem;
        }
    }
}

void Graph::ChangeBoundsY() {
    for (int index = 0; index < yCoord.size(); ++index) {
        changeBoundsByNew(index);
    }
}

void Graph::changeBoundsByNew(int index) {
    if (activePointsNum > yCoord[index].vertices->size()) {
        activePointsNum = yCoord[index].vertices->size();
    }
    for (auto elem : *(yCoord[index]).vertices) {
        if (elem < yMin) {
            yMin = elem;
        }

        if (elem > yMax) {
            yMax = elem;
        }
    }
}

void Graph::enableFunc(int index, bool enable) {
    if (index >= yCoord.size()) {
        LOGS("ERROR >>> out of bounds\n")
    }
    yCoord[index].notForgotten = enable;
}

bool Graph::isEnabled(int index) {
    if (index >= yCoord.size()) {
        LOGS("ERROR >>> out of bounds\n")
    }
    return yCoord[index].notForgotten;
}

void Graph::changeEnable(int index) {
    if (isEnabled(index)) {
        enableFunc(index, false);
    }
    else {
        enableFunc(index, true);
    }
}

sf::VertexArray Graph::drawOneLine(int nGraph, int nPair) const {
    sf::FloatRect place = background.getGlobalBounds();

    sf::VertexArray line (sf::Lines, 2);
        
    line[0].position = sf::Vector2f(
        place.left + ((double) (*xCoord)[nPair]) / (xMax - xMin) * place.width, 
        place.top + place.height - ((double) (*(yCoord[nGraph].vertices))[nPair]) / (yMax - yMin) * place.height
    );
    line[1].position = sf::Vector2f(
        place.left + ((double) (*xCoord)[nPair - 1]) / (xMax - xMin) * place.width, 
        place.top + place.height - ((double) (*(yCoord[nGraph].vertices))[nPair - 1]) / (yMax - yMin) * place.height
    );
    
    line[0].color = yCoord[nGraph].color;
    line[1].color = yCoord[nGraph].color;

    return line;
}
    
void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);

    if (activePointsNum == 1) {
        return;
    }

    //LOGS("INFO >>> graph %p is being drawn\n", this)

    for (int nGraph = 0; nGraph < yCoord.size(); ++nGraph) {
        if (yCoord[nGraph].notForgotten) {
            for (int i = 1; i < activePointsNum; ++i) {
                sf::VertexArray line = drawOneLine(nGraph, i);
                //LOGS("INFO >>> line (%d, %d) -> (%d, %d) needs to be drawn\n", line.getBounds().left, line.getBounds().top, line.getBounds().left + line.getBounds().width, line.getBounds().top + line.getBounds().height)
                target.draw(line);
            }
        }
    }
}