#include "AxeItem.h"

AxeItem::AxeItem(
	const std::string &name,
	uint8_t rarity,
	TextureId textureId,
	uint8_t power)
	:
	ToolItem(name, Item::Type::Axe, rarity, textureId, power)
{}