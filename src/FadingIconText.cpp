#include "FadingIconText.h"
#include "TextureData.h"

FadingIconText::FadingIconText(
	const sf::Vector2f &position,
	const sf::Vector2f &velocity,
	const sf::String &string,
	const sf::Color &fillColor,
	unsigned int characterSize,
	TextureId textureId,
	float durationSecs)
	:
	FadingText(
		position,
		velocity,
		string,
		fillColor,
		characterSize,
		durationSecs),
	sprite_(
		TextureData::getInstance().getTexture(textureId))
{
	const sf::FloatRect textLocalBounds = text_.getLocalBounds();

	const float gap = 2.0f;

	text_.setOrigin(
		sf::Vector2f(
			textLocalBounds.left,
			textLocalBounds.top + textLocalBounds.height * 0.5f));

	text_.setWorldPosition(
		sf::Vector2f(
			position.x + gap * 0.5f,
			position.y));

	const sf::Vector2f &spriteSize = sprite_.getSize();

	sprite_.setOrigin(
		sf::Vector2f(
			spriteSize.x,
			spriteSize.y * 0.5f));

	sprite_.setPosition(
		sf::Vector2f(
			position.x - gap * 0.5f,
			position.y));
}

void FadingIconText::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	sprite_.draw(target, states, offset, scale);
	FadingText::draw(target, states, offset, scale);
}

void FadingIconText::updatePosition_(float deltaTime)
{
	FadingText::updatePosition_(deltaTime);
	sprite_.move(velocity_ * deltaTime);
}

void FadingIconText::applyAlpha_(uint8_t alpha)
{
	FadingText::applyAlpha_(alpha);
	sprite_.setAlpha(alpha);
}