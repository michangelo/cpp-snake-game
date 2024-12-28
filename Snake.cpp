#include <vector>
#include <SFML/Graphics.hpp>
#include <list>

class Snake
{
protected:
	struct SnakeSegment
	{
		int x;
		int y;
		int size; // size of pixels in a segment
		int headColor;
		int bodyColor;
	};
private:
	std::vector<sf::RectangleShape> body();
	std::list<SnakeSegment> segmentBody;
public:
	Snake(int x, int y);
	void move(int x, int y);
	void grow();
	std::vector<sf::RectangleShape> getSnakeBody();
};
