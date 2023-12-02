#pragma once

#include "Hoverable.h"
#include "InterfaceDrawable.h"
#include <SFML/Window/Mouse.hpp>
#include <cstdint>

class Button :
	public Hoverable,
	public InterfaceDrawable
{
public:
	Button(
		const sf::Vector2f &position,
		const sf::Vector2f &size);

	virtual ~Button() = default;

	void update(float deltaTime);
	void updateOnMouseMove(const sf::Vector2f &mouseRelativePosition) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button);
	void updateOnMouseButtonRelease(sf::Mouse::Button button);

	virtual void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override = 0;
protected:
	virtual void applyScale_(float scale) = 0;
private:
	enum class State : uint8_t
	{
		None,
		Expand,
		Contract,
		Return
	};

	State state_;

	float scale_;
	float minScale_;
	float maxScale_;
	float velScale_;
};