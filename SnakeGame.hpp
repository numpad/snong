#ifndef SNAKEGAME_HPP
#define SNAKEGAME_HPP

#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include "tinyc2.h"

class SnakeGame {
	sf::IntRect area;
	int tileSize;
	int gridWidth, gridHeight;
	char *grid;

	sf::RectangleShape tile;

	/* Update & Timing */
	sf::Clock timestep;
	float timestepDuration;

	std::vector<sf::Keyboard::Key> inputs;

	/* Snake */
	struct {
		int x, y;
		int dx, dy;
		int length;
	} snake;

	sf::Keyboard::Key getInput();
public:

	SnakeGame(int, int, int, int);
	~SnakeGame();

	void setColor(sf::Color);

	void update();
	void draw(sf::RenderTarget &);

	void receiveInput();
	void each(std::function<void (char &, int, int, int, int)>);
};

#endif