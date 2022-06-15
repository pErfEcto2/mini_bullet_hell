#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "map"
#include "string"
#include "vector"

sf::Text textInit(std::string str, sf::Font &font, int size, sf::Vector2f pos);

enum GameState {
    start,
    game,
    end
};

class Bullet {
    public:
	    Bullet(sf::Vector2f pos, sf::Vector2f target, sf::Vector2f s);
	    void update();
		void draw(sf::RenderTarget& rt);
    private:
    	sf::RectangleShape bullet;
		sf::Vector2f pos;
		sf::Vector2f target;
		sf::Vector2f bulletSize;
		sf::Vector2f linSpeed;
		double length;
		sf::Vector2f originalPos;
};


class Object {
    private:
        sf::RectangleShape rect;
        sf::Vector2f vel;
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::Vector2f screenSize;
        int speed;
        std::map<std::string, bool> toMove;
        sf::Color color;
        std::vector<Bullet> bullets;
        time_t lastShoot = time(NULL);
    public:
        Object(sf::Vector2f p,
                 sf::Vector2f s,
                 int sp,
                 sf::Color c);
        void draw(sf::RenderWindow &w);
        void update();
        void control(sf::Keyboard &keyboard, sf::Event &event);
};

class Enemy {
    private:
        sf::RectangleShape rect;
        sf::Vector2f vel;
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::Vector2f screenSize;
        int speed;
        sf::Color color;
    public:
        Enemy(sf::Vector2f p,
                 sf::Vector2f s,
                 int sp,
                 sf::Color c);
        void update();
        void shoot();
        void draw(sf::RenderWindow &w);
};
