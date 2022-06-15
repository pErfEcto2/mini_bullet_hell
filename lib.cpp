#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "lib.hpp"
#include "iostream"
#include "cmath"
/*
sf::Vector2f operator+=(sf::Vector2f const &v, int const &i) {
    return sf::Vector2f(v.x + i, v.y + i);
}
*/

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
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i].draw(w);
    }
    w.draw(rect);
}

void Object::control(sf::Keyboard &keyboard, sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (keyboard.isKeyPressed(sf::Keyboard::W)) toMove["up"] = true;
        if (keyboard.isKeyPressed(sf::Keyboard::S)) toMove["down"] = true;
        if (keyboard.isKeyPressed(sf::Keyboard::A)) toMove["left"] = true;
        if (keyboard.isKeyPressed(sf::Keyboard::D)) toMove["right"] = true;

        if (keyboard.isKeyPressed(sf::Keyboard::Space) && time(NULL) - lastShoot > 0.2) {
            toMove["shoot"] = true;
            lastShoot = time(NULL);
        }
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

    if (toMove["shoot"]) {
        Bullet b(pos, sf::Vector2f(pos.x, pos.y - 5), sf::Vector2f(10, 15));
        bullets.push_back(b);
        toMove["shoot"] = false;
    }

    if (pos.x + size.x / 2 > screenSize.x) pos.x = screenSize.x - size.x / 2;
    if (pos.x - size.x / 2 < 0) pos.x = size.x / 2;
    if (pos.y + size.y / 2 > screenSize.y) pos.y = screenSize.y - size.y / 2;
    if (pos.y < screenSize.y / 2) pos.y = screenSize.y / 2 + size.y / 2;

    rect.setPosition(pos);

    for (int i = 0; i < bullets.size(); i++) {
        bullets[i].update();
    }
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
    if (-10 <= vel.x && vel.x <= 10) vel = sf::Vector2f((-1 + rand() % 3) * speed, 0);

    pos += vel;
    if (vel.x < 0) vel.x += speed / 20;
    else if (vel.x > 0) vel.x -= speed / 20;

    if (pos.x + size.x / 2 > screenSize.x) pos.x = screenSize.x - size.x / 2;
    if (pos.x - size.x / 2 < 0) pos.x = size.x / 2;

    rect.setPosition(pos);
}

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f target, sf::Vector2f s): pos(pos), target(target), bulletSize(s) {
	bullet.setPosition(pos);
	bullet.setSize(s);
	bullet.setOrigin(sf::Vector2f(bullet.getSize().x / 2, bullet.getSize().y / 2));
	linSpeed = target - pos; // profections of speedX and speedY
	length = sqrt((linSpeed.x * linSpeed.x) + (linSpeed.y * linSpeed.y));
	originalPos = pos;
	linSpeed.x /= length / 5;
	linSpeed.y /= length / 5;
}

void Bullet::update() {
	bullet.move(linSpeed);
}

void Bullet::draw(sf::RenderTarget& rt) {
	rt.draw(bullet);
}
