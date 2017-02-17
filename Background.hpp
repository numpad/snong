#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include "tinyc2.h"
#include "Random.hpp"

class Background {
	sf::RenderTexture texture;
	sf::Sprite sprite;

	/* Camera and screenshake */
	sf::View camera;
	Random randScreenShake;
	float screenShakeIntensity;

	sf::Color color;
public:
	sf::Vector2f defaultCameraPos;

	Background(sf::RenderTarget &, sf::Color color = sf::Color(55, 55, 55));

	void setCamera(c2v);
	void shake(float intensity = 20.0);

	void clear(sf::RenderTarget &);
};

#endif