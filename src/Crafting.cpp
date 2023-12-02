#include "Crafting.h"
#include <fstream>
#include <sstream>

Crafting::Crafting() :
	itemRecipes_()
{
	this->loadItemRecipes_("./data/item-recipes.txt");
}

const std::vector<ItemRecipe> &Crafting::getItemRecipes() const
{
	return itemRecipes_;
}

void Crafting::loadItemRecipes_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		fprintf(stderr, "Failed to open \"%s\" in Crafting::loadItemRecipes_\n", filePath.c_str());
		return;
	}

	std::string line;
	std::stringstream ss;

	while (std::getline(in, line))
	{
		ItemId productItemId;
		uint64_t numIngredients;
		std::vector<std::pair<ItemId, uint64_t>> ingredients;

		ss.clear();
		ss.str(line);

		ss >> productItemId >> numIngredients;

		ingredients.resize(numIngredients);

		for (uint64_t i = 0; i < numIngredients; ++i)
		{
			ss >> ingredients[i].first >> ingredients[i].second;
		}

		itemRecipes_.emplace_back(
			ItemRecipe(
				productItemId,
				ingredients));
	}

	in.close();
}