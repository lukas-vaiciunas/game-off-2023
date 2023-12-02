#pragma once

#include <SFML/System/Vector2.hpp>

class Shakable
{
public:
	Shakable(float maxOffset, float traumaDecay);

	virtual ~Shakable() = default;

	virtual void update(float deltaTime);
protected:
	sf::Vector2f offset_;
	float maxOffset_;
	float trauma_;
	float traumaDecay_;

	void shake_(float trauma);
};