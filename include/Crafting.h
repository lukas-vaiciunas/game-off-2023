#pragma once

#include "ItemRecipe.h"
#include <vector>
#include <string>

class Crafting
{
public:
	Crafting();

	const std::vector<ItemRecipe> &getItemRecipes() const;
private:
	std::vector<ItemRecipe> itemRecipes_;

	void loadItemRecipes_(const std::string &filePath);
};