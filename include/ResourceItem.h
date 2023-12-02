#pragma once

#include "Item.h"

class ResourceItem : public Item
{
public:
	ResourceItem(
		const std::string &name,
		uint8_t rarity,
		TextureId textureId);
};