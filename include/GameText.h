#pragma once

#include <SFML/Graphics/Text.hpp>

class GameText : public sf::Transformable
{
public:
	GameText();

	virtual ~GameText() = default;

	void setString(const sf::String &string);
	void setCharacterSize(unsigned int size);
	void setFillColor(const sf::Color &color);
	void setOutlineColor(const sf::Color &color);
	void setAlpha(uint8_t alpha);

	sf::FloatRect getLocalBounds() const;
	const sf::String &getString() const;
protected:
	sf::Text text_;
};