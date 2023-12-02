#include "HelmetItem.h"

HelmetItem::HelmetItem(
	const std::string &name,
	uint8_t rarity,
	TextureId textureId,
	uint64_t armor)
	:
	ArmorItem(name, Item::Type::Helmet, rarity, textureId, armor)
{}