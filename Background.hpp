#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>

class Background {
	sf::RenderTexture texture;
	sf::Sprite sprite;

	sf::Color color;
public:

	Background(sf::Vector2u, sf::Color color = sf::Color(33, 33, 33));

	void clear(sf::RenderTarget &);
};

#endif