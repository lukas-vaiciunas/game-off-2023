#pragma once

class EyeballState;

#include "Listener.h"
#include "InterfaceDrawable.h"
#include <SFML/Window/Mouse.hpp>

class Eyeball :
	public Listener,
	public InterfaceDrawable
{
public:
	Eyeball(const sf::Vector2f &position);

	~Eyeball();

	void onEvent(const Event &ev) override;

	void update(float deltaTime);
	void updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition);
	void updateOnMouseButtonPress(sf::Mouse::Button button);
	void updateOnMouseButtonRelease(sf::Mouse::Button button);

	bool isHovered() const;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	EyeballState *state_;

	sf::Vector2f position_;
};