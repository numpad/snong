#ifndef BALL_HPP
#define BALL_HPP

#include <math.h>

#include <SFML/Graphics.hpp>

#include "tinyc2.h"

class Ball {

	/* Physics */
	float radius;
	c2AABB collider;
	c2v vel;
	float speed;

	/* Graphics */
	sf::RectangleShape shape;

public:

	/* c2v position, float angle in degrees, float speed */
	Ball(c2v, float, float speed = 1.0);

	void update();
	void draw(sf::RenderTarget &);
};

#endif