#pragma once

#include "Fading.h"
#include "WorldText.h"
#include "AlarmClock.h"

class FadingText :
	public Fading,
	public WorldDrawable
{
public:
	FadingText(
		const sf::Vector2f &centerPosition,
		const sf::Vector2f &velocity,
		const sf::String &string,
		const sf::Color &fillColor,
		unsigned int characterSize,
		float durationSecs);

	virtual ~FadingText() = default;

	virtual void update(float deltaTime) override;

	virtual void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
protected:
	WorldText text_;

	sf::Vector2f velocity_;

	virtual void updatePosition_(float deltaTime);
	virtual void applyAlpha_(uint8_t alpha) override;
};