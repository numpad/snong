#ifndef BALL_HPP
#define BALL_HPP

#include <math.h>

#include <SFML/Graphics.hpp>

#include "tinyc2.h"

class Ball {

	/* Physics */
	float radiusMult;
	c2AABB collider;

	/* Graphics */
	sf::RectangleShape shape;

	sf::Clock timeAlive;
	float startTimeout;
public:
	float radius, speed;
	c2v vel;

	/* c2v position, float angle in degrees, float speed */
	Ball(c2v, float, float speed = 1.0);

	void bounce();

	void update();
	void draw(sf::RenderTarget &);

	c2AABB &getAABB();
};

#endif