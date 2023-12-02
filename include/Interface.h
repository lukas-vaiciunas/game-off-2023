#pragma once

#include "Hoverable.h"
#include "InterfaceDrawable.h"

class Interface :
	public Hoverable,
	public InterfaceDrawable
{
public:
	Interface(
		const sf::Vector2f &position,
		const sf::Vector2f &size);

	virtual ~Interface() = default;

	virtual void updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition) override;

	void toggle();
	void activate();
	void deactivate();

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override = 0;
protected:
	bool isActive_;
};