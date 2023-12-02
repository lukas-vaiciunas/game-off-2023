#include "ArmorItem.h"

ArmorItem::ArmorItem(
	const std::string &name,
	Type type,
	uint8_t rarity,
	TextureId textureId,
	uint64_t armor)
	:
	Item(name, type, rarity, textureId),
	armor_(armor)
{}

uint64_t ArmorItem::getArmor() const
{
	return armor_;
}