#include "WeaponItem.h"

WeaponItem::WeaponItem(
	const std::string &name,
	uint8_t rarity,
	TextureId textureId,
	uint64_t damage)
	:
	Item(name, Item::Type::Weapon, rarity, textureId),
	damage_(damage)
{}

uint64_t WeaponItem::getDamage() const
{
	return damage_;
}