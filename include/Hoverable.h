#pragma once

#include <SFML/System/Vector2.hpp>

class Hoverable
{
public:
	Hoverable(
		const sf::Vector2f &position,
		const sf::Vector2f &size);

	virtual ~Hoverable() = default;

	virtual void updateOnMouseMove(const sf::Vector2f &mouseRelativePosition);

	bool isHovered() const;
protected:
	sf::Vector2f position_;
	sf::Vector2f size_;

	bool isHovered_;
};