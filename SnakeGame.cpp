#include "SnakeGame.hpp"

SnakeGame::Direction SnakeGame::getInput() {
	if (SnakeGame::inputs.size() == 0)
		return SnakeGame::DIRECTION_UNKNOWN;
	
	SnakeGame::Direction out = SnakeGame::DIRECTION_UNKNOWN;
	
	sf::Keyboard::Key key = SnakeGame::inputs.at(0);

	if (key == SnakeGame::key_up)
		out = SnakeGame::DIRECTION_UP;
	else if (key == SnakeGame::key_down)
		out = SnakeGame::DIRECTION_DOWN;
	else if (key == SnakeGame::key_left)
		out = SnakeGame::DIRECTION_LEFT;
	else if (key == SnakeGame::key_right)
		out = SnakeGame::DIRECTION_RIGHT;
	
	SnakeGame::inputs.erase(SnakeGame::inputs.begin());

	return out;
}

SnakeGame::SnakeGame(int x, int y, int x2, int y2) {
	SnakeGame::area = sf::IntRect(x, y, x2 - x, y2 - y);
	SnakeGame::tileSize = 30;
	SnakeGame::gridWidth = SnakeGame::area.width / SnakeGame::tileSize;
	SnakeGame::gridHeight = SnakeGame::area.height / SnakeGame::tileSize;
	
	SnakeGame::grid = (char *)calloc(SnakeGame::gridWidth * SnakeGame::gridHeight, sizeof(char));

	SnakeGame::tile.setSize(sf::Vector2f(SnakeGame::tileSize, SnakeGame::tileSize));
	SnakeGame::tile.setFillColor(sf::Color::Red);

	SnakeGame::timestepDuration = 0.1;

	SnakeGame::inputs = std::vector<sf::Keyboard::Key>();

	SnakeGame::snake = {10, 5, 1, 0, 5};
}

SnakeGame::~SnakeGame() {
	if (SnakeGame::grid)
		free(SnakeGame::grid);
}

void SnakeGame::setColor(sf::Color color) {
	SnakeGame::tile.setFillColor(color);
}

void SnakeGame::setKeys(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right) {
	SnakeGame::key_up = up;
	SnakeGame::key_down = down;
	SnakeGame::key_left = left;
	SnakeGame::key_right = right;
}

void SnakeGame::receiveInput() {
	if (SnakeGame::inputs.size() > 3)
		return;
	
	sf::Keyboard::Key input = sf::Keyboard::Unknown;
	if (sf::Keyboard::isKeyPressed(SnakeGame::key_left) && !sf::Keyboard::isKeyPressed(SnakeGame::key_right)) {
		input = SnakeGame::key_left;
	}

	if (!sf::Keyboard::isKeyPressed(SnakeGame::key_left) && sf::Keyboard::isKeyPressed(SnakeGame::key_right)) {
		input = SnakeGame::key_right;
	}

	if (sf::Keyboard::isKeyPressed(SnakeGame::key_up) && !sf::Keyboard::isKeyPressed(SnakeGame::key_down)) {
		input = SnakeGame::key_up;
	}

	if (!sf::Keyboard::isKeyPressed(SnakeGame::key_up) && sf::Keyboard::isKeyPressed(SnakeGame::key_down)) {
		input = SnakeGame::key_down;
	}

	if (input != sf::Keyboard::Unknown)
		SnakeGame::inputs.push_back(input);
}

void SnakeGame::update() {

	/* Handle input */
	switch (SnakeGame::getInput()) {
		case SnakeGame::DIRECTION_LEFT:
			SnakeGame::snake.dx = -1;
			SnakeGame::snake.dy =  0;
			break;
		case SnakeGame::DIRECTION_RIGHT:
			SnakeGame::snake.dx =  1;
			SnakeGame::snake.dy =  0;
			break;
		case SnakeGame::DIRECTION_UP:
			SnakeGame::snake.dx =  0;
			SnakeGame::snake.dy = -1;
			break;
		case SnakeGame::DIRECTION_DOWN:
			SnakeGame::snake.dx =  0;
			SnakeGame::snake.dy =  1;
			break;
		default: break;
	};

	/* Handle update timeout */
	if (SnakeGame::timestep.getElapsedTime().asSeconds() < SnakeGame::timestepDuration) {
		return;
	}
	SnakeGame::timestep.restart();

	/* Update grid */
	SnakeGame::each([](char &current, int x, int y, int w, int h) {
		if (current > 0) --current;
	});

	/* Move snake */
	SnakeGame::snake.x += SnakeGame::snake.dx;
	SnakeGame::snake.y += SnakeGame::snake.dy;
	
	SnakeGame::grid[SnakeGame::snake.x + SnakeGame::snake.y * SnakeGame::gridWidth] = SnakeGame::snake.length;
}

void SnakeGame::draw(sf::RenderTarget &target) {
	SnakeGame::each([&target, this](char &current, int x, int y, int width, int height) {
			if (current) {
				SnakeGame::tile.setPosition(SnakeGame::area.left + x * SnakeGame::tileSize, SnakeGame::area.top + y * SnakeGame::tileSize);
				target.draw(SnakeGame::tile);
			}
		}
	);
}

void SnakeGame::each(std::function<void (char &, int, int, int, int)> func) {
	for (int y = 0; y < SnakeGame::gridHeight; ++y) {
		for (int x = 0; x < SnakeGame::gridWidth; ++x) {
			func(SnakeGame::grid[x + y * SnakeGame::gridWidth], x, y, SnakeGame::gridWidth, SnakeGame::gridHeight);
		}	
	}
}