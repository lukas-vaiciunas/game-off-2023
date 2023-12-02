#pragma once

#include "Particle.h"

class GravityParticle : public Particle
{
public:
	GravityParticle(
		const sf::Vector2f &position,
		const sf::Vector2f &velocity,
		float accelerationY,
		float floorY,
		uint8_t maxNumBounces,
		const sf::Texture &texture,
		float durationSecs);

	virtual void update(float deltaTime) override;
private:
	float accelerationY_;
	float floorY_;
	uint8_t maxNumBounces_;
	uint8_t numBounces_;
};