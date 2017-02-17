#ifndef SNAKEGAME_HPP
#define SNAKEGAME_HPP

#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include "tinyc2.h"

class SnakeGame {
	enum Direction {
		DIRECTION_UP, DIRECTION_DOWN,
		DIRECTION_LEFT, DIRECTION_RIGHT,
		DIRECTION_UNKNOWN
	};

	sf::IntRect area;
	int tileSize;
	int gridWidth, gridHeight;
	char *grid;

	sf::RectangleShape tile;

	/* Update & Timing */
	sf::Clock timestep;
	float timestepDuration;

	/* Snake */
	struct {
		int x, y;
		int dx, dy;
		int length;
	} snake;

	Direction getInput();
	std::vector<sf::Keyboard::Key> inputs;
	sf::Keyboard::Key key_up, key_down, key_left, key_right;

public:

	SnakeGame(int, int, int, int);
	~SnakeGame();

	void setColor(sf::Color);
	void setKeys(sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key, sf::Keyboard::Key);

	void update();
	void draw(sf::RenderTarget &);

	void receiveInput();
	void each(std::function<void (char &, int, int, int, int)>);
};

#endif