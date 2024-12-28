// Team Charlie

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>


class Snake {
public:
    Snake(int x, int y) {
        body.push_back(sf::RectangleShape(sf::Vector2f(20, 20)));
        body[0].setPosition(x, y);
        body[0].setFillColor(sf::Color::Green);
    }

    void move(int x, int y) {
        for (int i = body.size() - 1; i > 0; i--) {
            body[i].setPosition(body[i - 1].getPosition());
        }
        body[0].move(x, y);
    }


    void grow() {// Add a new rectangle to the end of the snake
        for (int i = 0; i < 20; i++) {//calls constructor to create new block set to 20 pixels and green
            body.push_back(sf::RectangleShape(sf::Vector2f(20, 20)));
            body[body.size() - 1].setPosition(body[body.size() - 2].getPosition());
            body[body.size() - 1].setFillColor(sf::Color::Green);// sets color of new block
        }      
    }

    std::vector<sf::RectangleShape> body;
};

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

void sleep(int t) {
    std::this_thread::sleep_for(std::chrono::microseconds(t));
}

int runGame() {

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

    Snake snake(400, 300);
    Fruit fruit;

    int x = 0, y = 0;
    
    int score = 0;
    int pauseTime = 5000;

    sf::Font font;
    font.loadFromFile("ariali.ttf");// Ensure this file is in the same directory as the executable
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    x = -1;
                    y = 0;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    x = 1;
                    y = 0;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    x = 0;
                    y = -1;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    x = 0;
                    y = 1;
                }
            }
        }
        // Check if snake is out of bounds
        if (snake.body[0].getPosition().x < 0 || snake.body[0].getPosition().x > 780 ||
            snake.body[0].getPosition().y < 0 || snake.body[0].getPosition().y > 580) {
            window.close();
        }
        // Check if snake has collided with itself
        for (int i = 1; i < snake.body.size(); i++) {
            if (snake.body[0].getPosition() == snake.body[i].getPosition()) {
                window.close();
            }
        }
        // Check if snake has eaten fruit
        if (snake.body[0].getGlobalBounds().intersects(fruit.fruit.getGlobalBounds())) {

            fruit.spawn();
            snake.grow();
            pauseTime = pauseTime * 0.97; // Speed up the game by 3% every time the snake eats a fruit
            score++;
            //text.setString("Score: " + std::to_string(score));
        }
        
        snake.move(x, y);
        // Draw everything
        window.clear();
        window.draw(fruit.fruit);
        sleep(pauseTime); // Slow down the game
        for (int i = 0; i < snake.body.size(); i++) {
            window.draw(snake.body[i]);
        }
        text.setPosition(10, 10);
        window.draw(text);
        window.display();
        text.setString("Score: " + std::to_string(score));               
    }
    return score;
}

int main() {
    
    std::cout << "Would you like to play Snake? (y/n)" << std::endl;
    char choice;
    std::cin >> choice;
    
    if (choice == 'y') {
        int score = runGame();
        std::cout << "Your score was " << score << std::endl;
        main();
    }
    else {
        return 0;
    }
};
