#ifndef SNAKEGAME_HPP
#define SNAKEGAME_HPP

#include <SFML/Graphics.hpp>
#include "tinyc2.h"

class SnakeGame {
	sf::IntRect area;
	int tileSize;
	int gridWidth, gridHeight;
	bool *grid;

	sf::RectangleShape tile;
public:

	SnakeGame(int, int, int, int);
	~SnakeGame();

	void update();
	void draw(sf::RenderTarget &);
};

#endif