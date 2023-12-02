#include "TextButton.h"
#include "Config.h"

TextButton::TextButton(
	const sf::Vector2f &centerPosition,
	const std::string &textString,
	uint32_t characterSize)
	:
	Button(
		sf::Vector2f(0.0f, 0.0f),
		sf::Vector2f(0.0f, 0.0f)),
	text_()
{
	text_.setString(textString);
	text_.setCharacterSize(characterSize);
	text_.setFillColor(sf::Color(225, 225, 225));
	text_.setOutlineColor(sf::Color(0, 0, 0));
	
	const sf::FloatRect textLocalBounds = text_.getLocalBounds();

	text_.setOrigin(
		sf::Vector2f(
			textLocalBounds.left + textLocalBounds.width * 0.5f,
			textLocalBounds.top + textLocalBounds.height * 0.5f));

	text_.setInterfacePosition(centerPosition);

	const float invInterfaceScale = 1.0f / Config::Interface::scale;

	size_ = sf::Vector2f(
		textLocalBounds.width * invInterfaceScale,
		textLocalBounds.height * invInterfaceScale);

	position_ = centerPosition - size_ * 0.5f;
}

void TextButton::setFillColor(const sf::Color &color)
{
	text_.setFillColor(color);
}

void TextButton::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	text_.draw(target, states, scale);
}

void TextButton::applyScale_(float scale)
{
	text_.setScale(
		sf::Vector2f(
			scale,
			scale));
}