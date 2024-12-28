

class Environment
{
private:
	bool playGame{ false };
	int score{ 0 };

public:
	void startGame();
	void runGame();
	void sleep(int t);
};
