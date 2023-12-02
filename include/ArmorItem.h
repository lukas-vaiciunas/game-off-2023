#pragma once

#include "Item.h"

class ArmorItem : public Item
{
public:
	ArmorItem(
		const std::string &name,
		Type type,
		uint8_t rarity,
		TextureId textureId,
		uint64_t armor);

	virtual ~ArmorItem() = default;

	uint64_t getArmor() const;
private:
	uint64_t armor_;
};