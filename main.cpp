#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "lib.hpp"

int main() {
    sf::RenderWindow w(sf::VideoMode(200, 200), "Mini bullet hell", sf::Style::Fullscreen);
    w.setFramerateLimit(60);

    sf::Vector2i screenSize = {sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height};
    sf::Event event;

    Object object(sf::Vector2f(screenSize.x / 2, screenSize.y / 2), // position
                    sf::Vector2f(40, 40), // size
                    20, // speed
                    sf::Color::White, // color
                    sf::Vector2f(0, 0)); // acceleration
    
    sf::Keyboard keyboard;

    while (w.isOpen()) {
        while (w.pollEvent(event)) {
            if (event.Closed || event.key.code == sf::Keyboard::Escape) w.close();

            object.move(keyboard, event);
        }
        object.update();
        
        w.clear(sf::Color::Black);
        object.draw(w);
        w.display();
    }

    return 0;
}