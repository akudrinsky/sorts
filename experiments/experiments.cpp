#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Sort algorithms");
    
    sf::Texture texture;
    texture.loadFromFile("data/background.jpg");

    sf::Sprite spite(texture);
    spite.scale(window.getSize().x / spite.getLocalBounds().width, 
                window.getSize().y / spite.getLocalBounds().height);
    spite.setColor(sf::Color(255, 204, 229, 10));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.clear();
        window.draw(spite);
        window.display();
    }

    return 0;
}