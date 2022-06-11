#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "lib.hpp"
#include "iostream"
/*
sf::Vector2f operator+=(sf::Vector2f const &v, int const &i) {
    return sf::Vector2f(v.x + i, v.y + i);
}*/

Object::Object(sf::Vector2f p,
                  sf::Vector2f s,
                  int sp,
                  sf::Color c) {
    pos = p;
    size = s;
    speed = sp;
    color = c;
    vel = sf::Vector2f(0, 0);
    rect = sf::RectangleShape(size);
    rect.setOrigin(size.x / 2, size.y / 2);
    rect.setPosition(pos);
    rect.setFillColor(color);
    screenSize = {sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height};
}

void Object::draw(sf::RenderWindow &w) {
    w.draw(rect);
}

void Object::move(sf::Keyboard &keyboard, sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (keyboard.isKeyPressed(sf::Keyboard::W)) toMove["up"] = true;
        if (keyboard.isKeyPressed(sf::Keyboard::S)) toMove["down"] = true;
        if (keyboard.isKeyPressed(sf::Keyboard::A)) toMove["left"] = true;
        if (keyboard.isKeyPressed(sf::Keyboard::D)) toMove["right"] = true;
    }
    else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::W) toMove["up"] = false;
        if (event.key.code == sf::Keyboard::S) toMove["down"] = false;
        if (event.key.code == sf::Keyboard::A) toMove["left"] = false;
        if (event.key.code == sf::Keyboard::D) toMove["right"] = false;
    }
}

void Object::update() {
    pos += vel;

    if (toMove["up"]) vel.y = -speed;
    else if (toMove["down"]) vel.y = speed;
    else vel.y = 0;
    if (toMove["left"]) vel.x = -speed;
    else if (toMove["right"]) vel.x = speed;
    else vel.x = 0;

    if (pos.x + size.x / 2 > screenSize.x) pos.x = screenSize.x - size.x / 2;
    if (pos.x - size.x / 2 < 0) pos.x = size.x / 2;
    if (pos.y + size.y / 2 > screenSize.y) pos.y = screenSize.y - size.y / 2;
    if (pos.y - size.y / 2 < 0 ) pos.y = size.y / 2;

    rect.setPosition(pos);
}

sf::Text textInit(std::string str, sf::Font &font, int size, sf::Vector2f pos) {
    sf::Text t;
    t.setFont(font);
    t.setString(str);
    t.setCharacterSize(size);
    t.setPosition(pos);
    t.setOrigin(t.getLocalBounds().width / 2, t.getLocalBounds().height / 2);
    return t;
}

Enemy::Enemy(sf::Vector2f p,
                  sf::Vector2f s,
                  int sp,
                  sf::Color c) {
    pos = p;
    size = s;
    speed = sp;
    color = c;
    vel = sf::Vector2f(0, 0);
    rect = sf::RectangleShape(size);
    rect.setOrigin(size.x / 2, size.y / 2);
    rect.setPosition(pos);
    rect.setFillColor(color);
    screenSize = {sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height};
}

void Enemy::draw(sf::RenderWindow &w) {
    w.draw(rect);
}

void Enemy::update() {
    //std::cout << vel.x << std::endl;
    if (-10 <= vel.x && vel.x <= 10) vel = sf::Vector2f((-5 + rand() % 11) * speed, 0);

    pos += vel;
    if (vel.x < 0) vel.x += speed / 1.2;
    else if (vel.x > 0) vel.x -= speed / 1.2;

    if (pos.x + size.x / 2 > screenSize.x) pos.x = screenSize.x - size.x / 2;
    if (pos.x - size.x / 2 < 0) pos.x = size.x / 2;

    rect.setPosition(pos);
}
