#include "Obstacle.hpp"

Obstacle::Obstacle(c2v min, c2v max) {
	Obstacle::aabb.min = min;
	Obstacle::aabb.max = max;
	
	Obstacle::shape.setPosition(Obstacle::aabb.min.x, Obstacle::aabb.min.y);
	Obstacle::shape.setSize(sf::Vector2f(Obstacle::aabb.max.x - Obstacle::aabb.min.x, Obstacle::aabb.max.y - Obstacle::aabb.min.y));
	Obstacle::shape.setFillColor(sf::Color(233, 233, 233));
}

void Obstacle::draw(sf::RenderTarget &target) {
	target.draw(Obstacle::shape);
}

c2AABB &Obstacle::getAABB() {
	return Obstacle::aabb;
}
