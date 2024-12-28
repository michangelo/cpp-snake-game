#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Snake
{
private:
	std::vector<sf::RectangleShape> body;
public:
	Snake(int x, int y)
	{
		body.push_back(sf::RectangleShape(sf::Vector2f(20, 20)));
		body[0].setPosition(x, y);
		body[0].setFillColor(sf::Color::Yellow);
	}

	void move(int x, int y) {
		for (int i = body.size() - 1; i > 0; i--) 
		{
			body[i].setPosition(body[i - 1].getPosition());
			body[i].setPosition(body[i - 1].getPosition().x, body[i - 1].getPosition().y);
		}
		body[0].move(x, y);
		}
	
	void grow() // Add a new rectangle to the end of the snake
	{
			body.push_back(sf::RectangleShape(sf::Vector2f(20, 20)));
			body[body.size() - 1].setPosition(body[body.size() - 2].getPosition());
			body[body.size() - 1].setFillColor(sf::Color::Green);
	}
	// Access snake body
public:
	std::vector<sf::RectangleShape> getSnakeBody()
	{
		return body;
	}
};
