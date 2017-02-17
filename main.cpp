#include <stdio.h>
#include <stdlib.h>

#include <SFML/Graphics.hpp>

#include "Random.hpp"
#include "Background.hpp"
#include "Ball.hpp"
#include "Obstacle.hpp"
#include "Obstacles.hpp"
#include "SnakeGame.hpp"

#define TINYC2_IMPL
#include "tinyc2.h"

int main(int argc, char *argv[]) {
	
	sf::RenderWindow window(sf::VideoMode(1018, 618), "Pong x Snake", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
	
	Background background(window);
	Ball ball(c2V(window.getSize().x / 2.0, window.getSize().y / 2.0), Random(0.0, 360.0)(), 6.25);

	Obstacles obstacles;
	obstacles.add(Obstacle(c2V(0, 0), c2V(window.getSize().x, 24)));
	obstacles.add(Obstacle(c2V(0, window.getSize().y - 24), c2V(window.getSize().x, window.getSize().y)));
	obstacles.add(Obstacle(c2V(0, 24), c2V(24, window.getSize().y - 24)));
	obstacles.add(Obstacle(c2V(window.getSize().x - 24, 24), c2V(window.getSize().x, window.getSize().y - 24)));
	
	SnakeGame game1(24, 24, window.getSize().x / 2.0 - 5.0, window.getSize().y - 24);
	game1.setColor(sf::Color(50, 115, 186));
	SnakeGame game2(window.getSize().x / 2.0 + 5.0, 24, window.getSize().x - 24, window.getSize().y - 24);
	game2.setColor(sf::Color(186, 115, 50));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					break;
				default:
					break;
			};
		}

		game1.receiveInput();
		game2.receiveInput();
		
		game1.update();
		game2.update();

		ball.update();
		obstacles.collide(ball, background);

		/* Rendering */
		background.clear(window);
		obstacles.draw(window);
		game1.draw(window);
		game2.draw(window);

		ball.draw(window);
		window.display();
	}

	return 0;
}
