#pragma once

#include "InterfaceDrawable.h"
#include <SFML/Window/Mouse.hpp>

class EyeballState : public InterfaceDrawable
{
public:
	EyeballState();

	virtual ~EyeballState() = default;

	virtual void update(float deltaTime) {}
	virtual void updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition) {}
	virtual void updateOnMouseButtonPress(sf::Mouse::Button button) {}
	virtual void updateOnMouseButtonRelease(sf::Mouse::Button button) {}

	virtual bool isHovered() const = 0;

	virtual void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override {}
};