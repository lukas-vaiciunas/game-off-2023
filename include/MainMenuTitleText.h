#pragma once

#include "InterfaceText.h"

class MainMenuTitleText : public InterfaceDrawable
{
public:
	MainMenuTitleText(const sf::Vector2f &centerWindowPosition);

	void draw(
		sf::RenderTarget &target, 
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	InterfaceText banishedText_;
	InterfaceText preyText_;
};