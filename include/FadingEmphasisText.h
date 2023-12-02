#pragma once

#include "FadingText.h"

class FadingEmphasisText : public FadingText
{
public:
	FadingEmphasisText(
		const sf::Vector2f &centerPosition,
		const sf::Vector2f &velocity,
		const sf::String &string,
		const sf::Color &fillColor,
		unsigned int characterSize,
		float durationSecs);

	void update(float deltaTime) override;
private:
	enum class State : uint8_t
	{
		None,
		Expanding,
		Contracting
	};

	State state_;

	float scale_;
	float minScale_;
	float maxScale_;
	float velScale_;

	void updateScale_();
};