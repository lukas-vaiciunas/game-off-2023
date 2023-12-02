#pragma once

#include "GameSprite.h"
#include "InterfaceDrawable.h"

class InterfaceSprite :
	public GameSprite,
	public InterfaceDrawable
{
public:
	InterfaceSprite(const sf::Texture &texture);
	InterfaceSprite(const sf::Texture &texture, const sf::Vector2f &size);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
};