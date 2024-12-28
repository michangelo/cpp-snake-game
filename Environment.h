#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Food.h"
#include "Snake.h"

class Environment
{
private:
    bool playGame{ false };
    int score{ 0 };

public:
    // Constructor
    Environment()
    {

    }
    // Asks the user if they would like to play and is the primary 
    // function for starting the game
    void startGame()
    {
        do
        {
            std::cout << "Welcome to snake, would you like to play? (y/n)" << std::endl;
            char choice;
            std::cin >> choice;
            if (choice == 'y') {
                playGame = true;
                int score = runGame();
                std::cout << "Your score was " << score << std::endl;
            }
            else {

                return;
            }
        } while (playGame == true);
    }

    // Controls in game functionality
    int runGame()
    {
        srand(time(NULL));

        sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

        Snake snake(400, 300);
        Fruit fruit;

        int x = 0, y = 0;

        int score = 0;
        int pauseTime = 100000;//changed

        
        sf::Font font;
        font.loadFromFile( "C:/Users/brian/source/repos/HelloWorld/ariali.ttf" );// Must include full file path to font
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setStyle(sf::Text::Regular);
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
            if (snake.getSnakeBody()[0].getPosition().x < 0 || snake.getSnakeBody()[0].getPosition().x > 780 ||
                snake.getSnakeBody()[0].getPosition().y < 0 || snake.getSnakeBody()[0].getPosition().y > 580) {
                window.close();
            }
            // Check if snake has collided with itself
            for (int i = 1; i < snake.getSnakeBody().size(); i++) {
                if (snake.getSnakeBody()[0].getPosition() == snake.getSnakeBody()[i].getPosition()) {
                    window.close();
                }
            }
            // Check if snake has eaten fruit
            if (snake.getSnakeBody()[0].getGlobalBounds().intersects(fruit.fruit.getGlobalBounds())) {
                fruit.spawn();
                snake.grow();
                pauseTime = pauseTime * 0.98; // Speed up the game by 2% every time the snake eats a fruit
                score++;
            }

            snake.move(x * 20, y * 20);//changed to move 20 pixels at a time
            // Draw everything
            window.clear();
            window.draw(fruit.fruit);
            sleep(pauseTime); // Slow down the game
            for (int i = 0; i < snake.getSnakeBody().size(); i++) {
                window.draw(snake.getSnakeBody()[i]);
            }
            text.setPosition(10, 10);
            window.draw(text);
            window.display();
            text.setString("Score: " + std::to_string(score));
        }
        return score;
    }

    // Sets the clock time
    void sleep(int t)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(t));
    }
};
