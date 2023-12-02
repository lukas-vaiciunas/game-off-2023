#pragma once

class CraftingInterface;

#include "InterfaceDrawable.h"
#include <SFML/Window/Mouse.hpp>

class CraftingInterfaceState : public InterfaceDrawable
{
public:
	CraftingInterfaceState(CraftingInterface &parent);

	virtual ~CraftingInterfaceState() = default;

	virtual void updateOnEvent() {}
	virtual void update(float deltaTime) {}
	virtual void updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition) {}
	virtual void updateOnMouseWheelScroll(float delta) {}
	virtual void updateOnMouseButtonPress(sf::Mouse::Button button) {}
	virtual void updateOnMouseButtonRelease(sf::Mouse::Button button) {}

	virtual void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override {}
protected:
	CraftingInterface &parent_;
};