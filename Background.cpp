#include "Background.hpp"

Background::Background(sf::Vector2u screenSize, sf::Color color) {
	Background::color = color;

	if (!Background::texture.create(screenSize.x * 0.01, screenSize.y)) {
		puts("Failed creating background texture!");
	}

	/* Draw the middle lines */
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(Background::texture.getSize().x, screenSize.x * 0.01));
	shape.setFillColor(sf::Color(233, 233, 233));
	int count = 0;
	for (unsigned int y = 0; y < screenSize.y; y += shape.getSize().y) {
		if ((count++ % 2) == 0) {
			shape.setPosition(0, y);
			Background::texture.draw(shape);
		}
	}

	Background::sprite.setTexture(Background::texture.getTexture());
	Background::sprite.setOrigin(sf::Vector2f(Background::texture.getTexture().getSize().x / 2.0, 0));
	Background::sprite.setPosition(screenSize.x / 2, 0);
}

void Background::clear(sf::RenderTarget &target) {
	target.clear(sf::Color(33, 33, 33));
	target.draw(Background::sprite);
}