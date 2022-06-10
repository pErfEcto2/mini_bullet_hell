#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "map"
#include "string"

class Object {
    private:
        sf::RectangleShape rect;
        sf::Vector2f vel;
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::Vector2f screenSize;
        int speed;
        sf::Vector2f accel;
        std::map<std::string, bool> toMove;
        sf::Color color;
    public:
        Object(sf::Vector2f p,
                 sf::Vector2f s,
                 int sp,
                 sf::Color c,
                 sf::Vector2f ac);
        void draw(sf::RenderWindow &w);
        void update();
        void move(sf::Keyboard &keyboard, sf::Event &event);
};