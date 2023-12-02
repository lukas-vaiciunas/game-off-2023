#pragma once

#include "GameText.h"
#include "InterfaceDrawable.h"

class InterfaceText :
	public GameText,
	public InterfaceDrawable
{
public:
	InterfaceText();

	void setInterfacePosition(const sf::Vector2f &position);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
};