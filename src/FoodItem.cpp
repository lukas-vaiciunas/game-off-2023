#include "FoodItem.h"

FoodItem::FoodItem(
	const std::string &name,
	uint8_t rarity,
	TextureId textureId,
	uint64_t nutrition)
	:
	Item(name, Item::Type::Food, rarity, textureId),
	nutrition_(nutrition)
{}

uint64_t FoodItem::getNutrition() const
{
	return nutrition_;
}