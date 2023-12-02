#pragma once

#include "ToolItem.h"

class AxeItem : public ToolItem
{
public:
	AxeItem(
		const std::string &name,
		uint8_t rarity,
		TextureId textureId,
		uint8_t power);
};