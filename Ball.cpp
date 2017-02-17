#include "Ball.hpp"

Ball::Ball(c2v pos, float angle, float speed) {
	Ball::radius = 8.0;
	Ball::radiusMult = 1.0;
	
	Ball::collider.min = c2V(pos.x - Ball::radius, pos.y - Ball::radius);
	Ball::collider.max = c2V(pos.x + Ball::radius, pos.y + Ball::radius);

	Ball::speed = speed;
	Ball::vel = c2V(sin(angle * (M_PI / 180.0)), cos(angle * (M_PI / 180.0)));

	Ball::shape.setSize(sf::Vector2f(Ball::radius * 2.0, Ball::radius * 2.0));
	Ball::shape.setOrigin(sf::Vector2f(Ball::shape.getSize().x / 2.0, Ball::shape.getSize().x / 2.0));
	Ball::shape.setFillColor(sf::Color(233, 233, 233));
	Ball::shape.setPosition(Ball::collider.min.x + Ball::radius, Ball::collider.min.y + Ball::radius);

	Ball::startTimeout = 1.0;
}

void Ball::bounce() {
	Ball::radiusMult = 2.65;
}

void Ball::update() {
	if (Ball::timeAlive.getElapsedTime().asSeconds() < Ball::startTimeout) {
		Ball::shape.rotate((1.0 - Ball::timeAlive.getElapsedTime().asSeconds() / Ball::startTimeout) * 20.0);
	} else {
		/* Shrink to normal size */
		if (Ball::radiusMult > 1.0)
			Ball::radiusMult *= 0.8;
		else
			Ball::radiusMult = 1.0;
		
		/* Calculcate velocity */
		Ball::vel = c2Mulvs(c2Norm(Ball::vel), Ball::speed);

		/* Calculcate new aabb */	
		Ball::collider.min = c2Add(Ball::collider.min, Ball::vel);
		Ball::collider.max = c2Add(Ball::collider.min, c2V(Ball::radius * 2, Ball::radius * 2));

		/* Update Graphics */
		float velAngle = atan2(Ball::vel.y, Ball::vel.x) * (180.0 / M_PI);
		Ball::shape.setRotation(velAngle);
		Ball::shape.setScale(radiusMult, radiusMult);
		Ball::shape.setPosition(Ball::collider.min.x + Ball::radius, Ball::collider.min.y + Ball::radius);
	}

	
}

void Ball::draw(sf::RenderTarget &target) {
	target.draw(Ball::shape);
}

c2AABB &Ball::getAABB() {
	return Ball::collider;
}