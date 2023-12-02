#include "ChestplateItem.h"

ChestplateItem::ChestplateItem(
	const std::string &name,
	uint8_t rarity,
	TextureId textureId,
	uint64_t armor)
	:
	ArmorItem(name, Item::Type::Chestplate, rarity, textureId, armor)
{}