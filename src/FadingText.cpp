#include "FadingText.h"
#include "Config.h"

FadingText::FadingText(
	const sf::Vector2f &centerPosition,
	const sf::Vector2f &velocity,
	const sf::String &string,
	const sf::Color &fillColor,
	unsigned int characterSize,
	float durationSecs)
	:
	Fading(durationSecs),
	WorldDrawable(),
	text_(),
	velocity_(velocity)
{
	text_.setString(string);
	text_.setFillColor(fillColor);
	text_.setCharacterSize(characterSize);

	sf::FloatRect textLocalBounds = text_.getLocalBounds();

	text_.setOrigin(
		sf::Vector2f(
			textLocalBounds.left + textLocalBounds.width * 0.5f,
			textLocalBounds.top + textLocalBounds.height * 0.5f));

	text_.setWorldPosition(centerPosition);
}

void FadingText::update(float deltaTime)
{
	Fading::update(deltaTime);

	this->updatePosition_(deltaTime);
}

void FadingText::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	text_.draw(target, states, offset, scale);
}

void FadingText::updatePosition_(float deltaTime)
{
	text_.move(velocity_ * Config::World::scale * deltaTime);
}

void FadingText::applyAlpha_(uint8_t alpha)
{
	text_.setAlpha(alpha);
}