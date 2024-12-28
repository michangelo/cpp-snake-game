#pragma once
#include <SFML/Graphics.hpp>

class Fruit {
public:
    Fruit() {
        fruit.setRadius(10);
        fruit.setFillColor(sf::Color::Red);
        spawn();
    }

    void spawn() {
        int x = rand() % 78 + 1;
        int y = rand() % 58 + 1;
        fruit.setPosition(x * 10, y * 10);
    }

    sf::CircleShape fruit;
};
