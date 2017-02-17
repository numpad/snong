#include "Background.hpp"

Background::Background(sf::RenderTarget &target, sf::Color color) {
	Background::color = color;

	Background::defaultCameraPos = sf::Vector2f(target.getSize().x / 2.0, target.getSize().y / 2.0);
	Background::camera.setCenter(Background::defaultCameraPos);
	Background::camera.setSize(sf::Vector2f(Background::defaultCameraPos.x * 2.0, Background::defaultCameraPos.y * 2.0));

	Background::randScreenShake = Random(-1.0, 1.0);

	target.setView(Background::camera);

	if (!Background::texture.create(target.getSize().x * 0.01, target.getSize().y)) {
		puts("Failed creating background texture!");
	}

	/* Draw the middle lines */
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(Background::texture.getSize().x, target.getSize().x * 0.01));
	shape.setFillColor(sf::Color(233, 233, 233));
	int count = 0;
	for (unsigned int y = 0; y < Background::texture.getSize().y; y += shape.getSize().y) {
		if ((count++ % 2) == 0) {
			shape.setPosition(0, y);
			Background::texture.draw(shape);
		}
	}

	Background::sprite.setTexture(Background::texture.getTexture());
	Background::sprite.setOrigin(sf::Vector2f(Background::texture.getTexture().getSize().x / 2.0, 0));
	Background::sprite.setPosition(target.getSize().x / 2.0, 0);
}

void Background::setCamera(c2v pos) {
	Background::camera.setCenter(pos.x, pos.y);
}

void Background::shake(float intensity) {
	Background::screenShakeIntensity += intensity;
}

void Background::clear(sf::RenderTarget &target) {
	target.clear(Background::color);
	target.draw(Background::sprite);

	c2v offset = c2V(Background::defaultCameraPos.x, Background::defaultCameraPos.y);
	if (Background::screenShakeIntensity > 0.5) {
		Background::screenShakeIntensity *= 0.8;

		float ix = Background::randScreenShake();
		float iy = Background::randScreenShake();
		
		offset = c2Add(offset, c2Mulvs(c2Norm(c2V(ix, iy)), Background::screenShakeIntensity));
	}
	
	Background::setCamera(offset);
	target.setView(Background::camera);
}