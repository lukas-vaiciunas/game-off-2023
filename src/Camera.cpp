#include "Camera.h"
#include "Config.h"
#include "Constants.h"

Camera::Camera() :
	position_(0.0f, 0.0f),
	bounds_(0.0f, 0.0f)
{
	const float invWorldScale = 1.0f / Config::World::scale;

	bounds_.x = Constants::Map::width * Constants::tileSize - Config::Window::width * invWorldScale;
	bounds_.y = Constants::Map::height * Constants::tileSize - Config::Window::height * invWorldScale;
}

void Camera::center(const sf::Vector2f &position)
{
	const float invWorldScale = 1.0f / Config::World::scale;

	position_.x = position.x - Config::Window::width * 0.5f * invWorldScale;
	position_.y = position.y - Config::Window::height * 0.5f * invWorldScale;

	this->constrain_();
}

const sf::Vector2f &Camera::getPosition() const
{
	return position_;
}

void Camera::constrain_()
{
	if (position_.x < 0.0f)
	{
		position_.x = 0.0f;
	}

	if (position_.y < 0.0f)
	{
		position_.y = 0.0f;
	}

	if (position_.x > bounds_.x)
	{
		position_.x = bounds_.x;
	}

	if (position_.y > bounds_.y)
	{
		position_.y = bounds_.y;
	}
}