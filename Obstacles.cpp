#include "Obstacles.hpp"

Obstacles::Obstacles() {
	Obstacles::array = std::vector<Obstacle>();

}

void Obstacles::add(Obstacle o) {
	Obstacles::array.push_back(o);
}

void Obstacles::each(std::function<void (Obstacle &)> func) {
	for (auto &o : Obstacles::array) {
		func(o);
	}
}

void Obstacles::update() {

}

void Obstacles::collide(Ball &ball, Background &background) {
	Obstacles::each([&ball, &background](Obstacle &o){
		if (c2AABBtoAABB(ball.getAABB(), o.getAABB())) {
			c2Manifold collision;
			c2AABBtoAABBManifold(ball.getAABB(), o.getAABB(), &collision);

			if (fabs(collision.normal.x) == 1.0) {
				ball.vel.x *= -1.0;
			}

			if (fabs(collision.normal.y) == 1.0) {
				ball.vel.y *= -1.0;
			}

			ball.bounce();
			ball.speed *= 1.02;
			if (ball.speed > 14.5)
				ball.speed = 14.5;
			
			background.shake(c2Len(ball.vel) * 2.0);
		}
	});
}

void Obstacles::draw(sf::RenderTarget &target) {
	for (auto &o : Obstacles::array) {
		o.draw(target);
	}
}
