#include "ItemRecipe.h"

ItemRecipe::ItemRecipe(
	ItemId productItemId,
	const std::vector<std::pair<ItemId, uint64_t>> &ingredients)
	:
	ingredients_(ingredients),
	productItemId_(productItemId)
{}

ItemId ItemRecipe::getProductItemId() const
{
	return productItemId_;
}

const std::vector<std::pair<ItemId, uint64_t>> &ItemRecipe::getIngredients() const
{
	return ingredients_;
}