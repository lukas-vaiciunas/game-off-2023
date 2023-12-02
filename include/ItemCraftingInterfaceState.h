#pragma once

#include "CraftingInterfaceState.h"
#include "ItemRecipeCard.h"
#include "TextButton.h"

class ItemCraftingInterfaceState : public CraftingInterfaceState
{
public:
	ItemCraftingInterfaceState(
		CraftingInterface &parent,
		size_t itemRecipeIndex);

	void updateOnEvent() override;
	void update(float deltaTime) override;
	void updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button) override;
	void updateOnMouseButtonRelease(sf::Mouse::Button button) override;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	size_t itemRecipeIndex_;

	ItemRecipeCard itemRecipeCard_;

	InterfaceText requirementsText_;

	std::vector<InterfaceSprite> ingredientSprites_;
	std::vector<InterfaceText> ingredientAmountTexts_;
	std::vector<InterfaceSprite> ingredientStatusSprites_;

	uint64_t numIngredients_;

	TextButton backButton_;
	TextButton craftButton_;

	bool isCraftable_;

	void updateStatus_();
};