#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

#include "tinyc2.h"

class Obstacle {
	
	c2AABB aabb;

	sf::RectangleShape shape;

public:

	Obstacle(c2v, c2v);

	void draw(sf::RenderTarget &);

	c2AABB &getAABB();
};

#endif