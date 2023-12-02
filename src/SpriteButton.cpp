#include "SpriteButton.h"

SpriteButton::SpriteButton(
	const sf::Vector2f &centerPosition,
	const sf::Texture &texture)
	:
	Button(
		sf::Vector2f(0.0f, 0.0f),
		sf::Vector2f(0.0f, 0.0f)),
	sprite_(texture)
{
	const sf::Vector2f &spriteSize = sprite_.getSize();
	const sf::Vector2f halfSpriteSize = spriteSize * 0.5f;

	sprite_.setOrigin(halfSpriteSize);
	sprite_.setPosition(centerPosition);

	size_ = spriteSize;
	position_ = centerPosition - halfSpriteSize;
}

void SpriteButton::setPosition(const sf::Vector2f &position)
{
	position_ = position;
	sprite_.setPosition(position_ + sprite_.getSize() * 0.5f);
}

void SpriteButton::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	sprite_.draw(target, states, scale);
}

void SpriteButton::applyScale_(float scale)
{
	sprite_.setScale(
		sf::Vector2f(
			scale,
			scale));
}