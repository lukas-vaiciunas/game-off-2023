#include "ResourceItem.h"

ResourceItem::ResourceItem(
	const std::string &name,
	uint8_t rarity,
	TextureId textureId)
	:
	Item(name, Item::Type::Resource, rarity, textureId)
{}