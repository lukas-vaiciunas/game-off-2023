#pragma once

#include "Button.h"
#include "InterfaceSprite.h"

class SpriteButton : public Button
{
public:
	SpriteButton(
		const sf::Vector2f &centerPosition,
		const sf::Texture &texture);
	
	void setPosition(const sf::Vector2f &position);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	InterfaceSprite sprite_;

	void applyScale_(float scale) override;
};