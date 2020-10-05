#include "../include/graph.hpp"

Graph::Graph(const sf::RectangleShape& background, 
                std::vector<int>* xCoord, 
                std::vector<int>* initYCoord) 
                :
                background(background), 
                xCoord(xCoord), 
                resizeAlways(false),
                font(loadFromFile("/Library/Fonts/Arial.ttf")),
                textColor(sf::Color::Black) {

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
        if (!resizeAlways or resizeAlways and yCoord[index].notForgotten) {
            changeBoundsByNew(index);
        }
    }
}

void Graph::colorText(const sf::Color& newColor) {
    textColor = newColor;
}

void Graph::alwaysResize(bool mode) {
    resizeAlways = mode;
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
        throw std::out_of_range("enableFunc fail");
    }

    yCoord[index].notForgotten = enable;

    if (resizeAlways) {
        yMax = std::numeric_limits<double>::min(); 
        yMin = std::numeric_limits<double>::max();
        ChangeBoundsY();
    }

    // TODO manage inefficiency (every functions should store its bounds)
}

bool Graph::isEnabled(int index) {
    if (index >= yCoord.size()) {
        LOGS("ERROR >>> out of bounds\n")
        throw std::out_of_range("isEnabled fail");
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

void Graph::drawBoundsNumbers(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2f backgroundPlace = background.getPosition();
    sf::Vector2f backgroundSize = background.getSize();

    int justNear = 20;

    sf::Vector2f yMinLoc(backgroundPlace.x - justNear, backgroundPlace.y + backgroundSize.y);
    sf::Vector2f xMinLoc(backgroundPlace.x, backgroundPlace.y + backgroundSize.y + justNear);
    sf::Vector2f xMaxLoc(backgroundPlace.x + backgroundSize.x, backgroundPlace.y + backgroundSize.y + justNear);
    sf::Vector2f yMaxLoc(backgroundPlace.x - justNear, backgroundPlace.y);

    drawNum(xMin, xMinLoc, target, states);
    drawNum(xMax, xMaxLoc, target, states);
    drawNum(yMin, yMinLoc, target, states);
    drawNum(yMax, yMaxLoc, target, states);
}

void Graph::drawNum(double num, const sf::Vector2f& location, 
                sf::RenderTarget& target, sf::RenderStates states) const {
    
    sf::Text info(std::to_string(num), font, 20);
    info.setColor(textColor);

    const sf::FloatRect bounds(info.getLocalBounds());
    info.setOrigin(bounds.width / 2.0f + bounds.left, 
                    bounds.height / 2.0f + bounds.top);
    info.setPosition(location);

    target.draw(info, states);
}
    
void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);

    drawBoundsNumbers(target, states);

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