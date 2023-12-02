#include "PickaxeItem.h"

PickaxeItem::PickaxeItem(
	const std::string &name,
	uint8_t rarity,
	TextureId textureId,
	uint8_t power)
	:
	ToolItem(name, Item::Type::Pickaxe, rarity, textureId, power)
{}