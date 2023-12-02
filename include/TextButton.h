#pragma once

#include "Button.h"
#include "InterfaceText.h"

class TextButton : public Button
{
public:
	TextButton(
		const sf::Vector2f &centerPosition,
		const std::string &textString,
		uint32_t characterSize);

	void setFillColor(const sf::Color &color);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	InterfaceText text_;

	void applyScale_(float scale) override;
};