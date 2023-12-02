#pragma once

#include "ToolItem.h"

class PickaxeItem : public ToolItem
{
public:
	PickaxeItem(
		const std::string &name,
		uint8_t rarity,
		TextureId textureId,
		uint8_t power);
};