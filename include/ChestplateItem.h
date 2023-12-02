#pragma once

#include "ArmorItem.h"

class ChestplateItem : public ArmorItem
{
public:
	ChestplateItem(
		const std::string &name,
		uint8_t rarity,
		TextureId textureId,
		uint64_t armor);
};