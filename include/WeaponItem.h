#pragma once

#include "Item.h"

class WeaponItem : public Item
{
public:
	WeaponItem(
		const std::string &name,
		uint8_t rarity,
		TextureId textureId,
		uint64_t damage);

	uint64_t getDamage() const;
private:
	uint64_t damage_;
};