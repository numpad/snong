#ifndef OBSTACLES_HPP
#define OBSTACLES_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "tinyc2.h"
#include "Background.hpp"
#include "Ball.hpp"
#include "Obstacle.hpp"

class Obstacles {

	std::vector<Obstacle> array;

public:
	
	Obstacles();

	void add(Obstacle);

	void each(std::function<void (Obstacle &)>);
	void update();

	void collide(Ball &, Background &);

	void draw(sf::RenderTarget &);
};

#endif
