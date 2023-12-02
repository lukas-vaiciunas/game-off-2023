#include "Item.h"

Item::Item(
	const std::string &name,
	Type type,
	uint8_t rarity,
	TextureId textureId)
	:
	name_(name),
	type_(type),
	rarity_(rarity),
	textureId_(textureId)
{}

const std::string &Item::getName() const
{
	return name_;
}

Item::Type Item::getType() const
{
	return type_;
}

sf::Color Item::getRarityColor() const
{
	switch (rarity_)
	{
		case 2:
			return sf::Color(140, 208, 140);
		case 3:
			return sf::Color(144, 180, 236);
		case 4:
			return sf::Color(196, 156, 236);
		case 5:
			return sf::Color(236, 160, 160);
		case 6:
			return sf::Color(252, 252, 104);
	}

	return sf::Color(225, 225, 225);
}

TextureId Item::getTextureId() const
{
	return textureId_;
}