#pragma once

#include "TextureId.h"
#include <SFML/Graphics/Color.hpp>
#include <string>

class Item
{
public:
	enum class Type : uint8_t
	{
		Resource,
		Food,
		Weapon,
		Helmet,
		Chestplate,
		Axe,
		Pickaxe
	};

	Item(
		const std::string &name,
		Type type,
		uint8_t rarity,
		TextureId textureId);

	virtual ~Item() = default;

	const std::string &getName() const;
	Type getType() const;
	sf::Color getRarityColor() const;
	TextureId getTextureId() const;
private:
	std::string name_;
	Type type_;
	uint8_t rarity_;
	TextureId textureId_;
};