#include "Particle.h"

Particle::Particle(
	const sf::Vector2f &position,
	const sf::Vector2f &velocity,
	const sf::Texture &texture,
	float durationSecs)
	:
	Fading(durationSecs),
	WorldDrawable(),
	sprite_(texture),
	position_(position),
	velocity_(velocity)
{
	sprite_.setOrigin(sprite_.getSize() * 0.5f);
	sprite_.setPosition(position_);
}

void Particle::update(float deltaTime)
{
	Fading::update(deltaTime);

	this->updatePosition_(deltaTime);
}

void Particle::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	sprite_.draw(target, states, offset, scale);
}

void Particle::updatePosition_(float deltaTime)
{
	position_ += velocity_ * deltaTime;

	sprite_.setPosition(position_);
}

void Particle::applyAlpha_(uint8_t alpha)
{
	sprite_.setAlpha(alpha);
}