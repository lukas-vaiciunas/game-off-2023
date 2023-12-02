#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

class DriverInterface : public sf::Drawable
{
public:
	DriverInterface();

	virtual ~DriverInterface() = default;

	virtual void update(float deltaTime) = 0;
	virtual void updateOnMouseMove(int mouseX, int mouseY) = 0;
	virtual void updateOnMouseWheelScroll(float delta) = 0;
	virtual void updateOnMouseButtonPress(sf::Mouse::Button button) = 0;
	virtual void updateOnMouseButtonRelease(sf::Mouse::Button button) = 0;
	virtual void updateOnKeyPress(sf::Keyboard::Key key) = 0;

	virtual void draw(
		sf::RenderTarget &target,
		sf::RenderStates states) const override = 0;
};