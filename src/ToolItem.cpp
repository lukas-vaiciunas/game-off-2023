#include "ToolItem.h"

ToolItem::ToolItem(
	const std::string &name,
	Type type,
	uint8_t rarity,
	TextureId textureId,
	uint8_t power)
	:
	Item(name, type, rarity, textureId),
	power_(power)
{}

uint8_t ToolItem::getPower() const
{
	return power_;
}