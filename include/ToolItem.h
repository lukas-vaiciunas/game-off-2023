#pragma once

#include "Item.h"

class ToolItem : public Item
{
public:
	ToolItem(
		const std::string &name,
		Type type,
		uint8_t rarity,
		TextureId textureId,
		uint8_t power);
	
	virtual ~ToolItem() = default;

	uint8_t getPower() const;
private:
	uint8_t power_;
};