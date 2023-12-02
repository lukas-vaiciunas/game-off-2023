#pragma once

#include <SFML/System/Vector2.hpp>

class Camera
{
public:
	Camera();

	void center(const sf::Vector2f &position);

	const sf::Vector2f &getPosition() const;
private:
	sf::Vector2f position_;
	sf::Vector2f bounds_;

	void constrain_();
};