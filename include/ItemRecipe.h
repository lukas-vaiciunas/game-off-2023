#pragma once

#include "ItemId.h"
#include <vector>

class ItemRecipe
{
public:
	ItemRecipe(
		ItemId productItemId,
		const std::vector<std::pair<ItemId, uint64_t>> &ingredients);

	ItemId getProductItemId() const;
	const std::vector<std::pair<ItemId, uint64_t>> &getIngredients() const;
private:
	std::vector<std::pair<ItemId, uint64_t>> ingredients_;
	ItemId productItemId_;
};