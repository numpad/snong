#include "SnakeGame.hpp"

SnakeGame::SnakeGame(int x, int y, int x2, int y2) {
	SnakeGame::area = sf::IntRect(x, y, x2 - x, y2 - y);
	SnakeGame::tileSize = 30;
	SnakeGame::gridWidth = SnakeGame::area.width / SnakeGame::tileSize;
	SnakeGame::gridHeight = SnakeGame::area.height / SnakeGame::tileSize;
	
	SnakeGame::grid = (bool *)calloc(SnakeGame::gridWidth * SnakeGame::gridHeight, sizeof(bool));

	SnakeGame::tile.setSize(sf::Vector2f(SnakeGame::tileSize, SnakeGame::tileSize));
	SnakeGame::tile.setFillColor(sf::Color::Red);

}

SnakeGame::~SnakeGame() {
	if (SnakeGame::grid)
		free(SnakeGame::grid);
}

void SnakeGame::draw(sf::RenderTarget &target) {
	for (int y = 0; y < SnakeGame::gridHeight; ++y) {
		for (int x = 0; x < SnakeGame::gridWidth; ++x) {
			if (SnakeGame::grid[x + y * SnakeGame::gridWidth]) {
				SnakeGame::tile.setPosition(SnakeGame::area.left + x * SnakeGame::tileSize, SnakeGame::area.top + y * SnakeGame::tileSize);
				target.draw(SnakeGame::tile);
			}
		}	
	}
}
