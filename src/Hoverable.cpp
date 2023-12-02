#include "Hoverable.h"

Hoverable::Hoverable(
	const sf::Vector2f &position,
	const sf::Vector2f &size)
	:
	position_(position),
	size_(size),
	isHovered_(false)
{}

void Hoverable::updateOnMouseMove(const sf::Vector2f &mouseRelativePosition)
{
	isHovered_ = mouseRelativePosition.x > position_.x
		&& mouseRelativePosition.x < position_.x + size_.x
		&& mouseRelativePosition.y > position_.y
		&& mouseRelativePosition.y < position_.y + size_.y;
}

bool Hoverable::isHovered() const
{
	return isHovered_;
}