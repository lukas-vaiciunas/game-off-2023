#pragma once

#include "FadingText.h"
#include "WorldSprite.h"
#include "TextureId.h"

class FadingIconText : public FadingText
{
public:
	FadingIconText(
		const sf::Vector2f &position,
		const sf::Vector2f &velocity,
		const sf::String &string,
		const sf::Color &fillColor,
		unsigned int characterSize,
		TextureId textureId,
		float durationSecs);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
private:
	WorldSprite sprite_;

	void updatePosition_(float deltaTime) override;
	void applyAlpha_(uint8_t alpha) override;
};