#include <stdio.h>
#include <stdlib.h>

#include <SFML/Graphics.hpp>

#include "Random.hpp"
#include "Background.hpp"
#include "Ball.hpp"

#define TINYC2_IMPL
#include "tinyc2.h"

int main(int argc, char *argv[]) {
	
	sf::RenderWindow window(sf::VideoMode(900, 600), "Pong x Snake", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
	
	Background background(window.getSize());
	Ball ball(c2V(450, 300), Random(0.0, 360.0)(), 2.0);

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

		ball.update();

		/* Rendering */
		background.clear(window);
		ball.draw(window);
		window.display();
	}

	return 0;
}
