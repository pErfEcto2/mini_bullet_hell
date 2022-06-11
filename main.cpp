#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "lib.hpp"
#include "iostream"
#include "vector"
#include "map"

int main() {
    srand(time(NULL));

    sf::RenderWindow w(sf::VideoMode(200, 200), "Mini bullet hell", sf::Style::Fullscreen);
    w.setFramerateLimit(60);
    w.setMouseCursorVisible(false);

    GameState state = start;

    sf::Vector2i screenSize = {sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height};
    sf::Event event;

    Object man(sf::Vector2f(screenSize.x / 2, screenSize.y / 1.5), // position
                    sf::Vector2f(20, 20), // size
                    20, // speed
                    sf::Color::White); // color
    
    Enemy enemy(sf::Vector2f(screenSize.x / 2, 30), // position
                    sf::Vector2f(60, 60), // size
                    20, // speed
                    sf::Color::Red); // color
    
    sf::Keyboard keyboard;

    sf::Font arialFont;
    if (!arialFont.loadFromFile("src/arial.ttf")) {
        std::cout << "Could not load font" << std::endl;
        return 1;
    }

    std::map<std::string, sf::Text> text = {
        {"enter", textInit("PRESS ENTER TO START", arialFont, 30, sf::Vector2f(screenSize.x / 2, screenSize.y / 2 - 50))},
        {"escape", textInit("PRESS ESCAPE TO EXIT", arialFont, 30, sf::Vector2f(screenSize.x / 2, screenSize.y / 2 + 30))},
        {"r", textInit("PRESS R TO REPLAY", arialFont, 30, sf::Vector2f(screenSize.x / 2, screenSize.y / 2 + 60))},
    };

    while (w.isOpen()) {
        while (w.pollEvent(event)) {
            if (event.Closed || event.key.code == sf::Keyboard::Escape) w.close();
            switch (state) {
                case start:
                    if (event.type == sf::Event::KeyPressed && keyboard.isKeyPressed(sf::Keyboard::Enter)) state = game;
                    break;

                case game:
                    man.move(keyboard, event);
                
                case end:
                    break;
            }
        }
        w.clear(sf::Color::Black);
        switch (state) {
            case start:
                w.draw(text["enter"]);
                w.draw(text["escape"]);
                break;

            case game:
                man.update();
                enemy.update();
                man.draw(w);
                enemy.draw(w);
                break;

            case end:
                w.draw(text["r"]);
                w.draw(text["escape"]);
                break;
        }
        w.display();
    }
    return 0;
}