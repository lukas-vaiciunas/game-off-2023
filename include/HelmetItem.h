#pragma once

#include "ArmorItem.h"

class HelmetItem : public ArmorItem
{
public:
	HelmetItem(
		const std::string &name,
		uint8_t rarity,
		TextureId textureId,
		uint64_t armor);
};