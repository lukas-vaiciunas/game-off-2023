#include "GameText.h"
#include "FontData.h"
#include "Config.h"

GameText::GameText() :
	sf::Transformable(),
	text_()
{
	text_.setFont(FontData::getInstance().getFont());
}

void GameText::setString(const sf::String &string)
{
	text_.setString(string);
}

void GameText::setCharacterSize(unsigned int size)
{
	text_.setCharacterSize(size);
	text_.setOutlineThickness(size * Config::Text::outlineScale);
}

void GameText::setFillColor(const sf::Color &color)
{
	text_.setFillColor(color);
}

void GameText::setOutlineColor(const sf::Color &color)
{
	text_.setOutlineColor(color);
}

void GameText::setAlpha(uint8_t alpha)
{
	const sf::Color &fillColor = text_.getFillColor();
	const sf::Color &outlineColor = text_.getOutlineColor();

	text_.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, alpha));
	text_.setOutlineColor(sf::Color(outlineColor.r, outlineColor.g, outlineColor.b, alpha));
}

sf::FloatRect GameText::getLocalBounds() const
{
	return text_.getLocalBounds();
}

const sf::String &GameText::getString() const
{
	return text_.getString();
}