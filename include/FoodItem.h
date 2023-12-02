#pragma once

#include "Item.h"

class FoodItem : public Item
{
public:
	FoodItem(
		const std::string &name,
		uint8_t rarity,
		TextureId textureId,
		uint64_t nutrition);

	uint64_t getNutrition() const;
private:
	uint64_t nutrition_;
};