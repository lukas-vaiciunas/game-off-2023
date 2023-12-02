#include "GravityParticle.h"

GravityParticle::GravityParticle(
	const sf::Vector2f &position,
	const sf::Vector2f &velocity,
	float accelerationY,
	float floorY,
	uint8_t maxNumBounces,
	const sf::Texture &texture,
	float durationSecs)
	:
	Particle(position, velocity, texture, durationSecs),
	accelerationY_(accelerationY),
	floorY_(floorY - sprite_.getSize().y * 0.5f),
	maxNumBounces_(maxNumBounces),
	numBounces_(0)
{}

void GravityParticle::update(float deltaTime)
{
	Fading::update(deltaTime);

	position_ += velocity_ * deltaTime;

	if (position_.y >= floorY_)
	{
		position_.y = floorY_;

		if (numBounces_ < maxNumBounces_)
		{
			++numBounces_;

			velocity_.y /= -2.0f * numBounces_;
		}
		else
		{
			velocity_.x = 0.0f;
			velocity_.y = 0.0f;
		}
	}
	else
	{
		velocity_.y += accelerationY_ * deltaTime;
	}

	sprite_.setPosition(position_);
}