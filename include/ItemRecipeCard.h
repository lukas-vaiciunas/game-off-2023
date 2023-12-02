#pragma once

class ItemRecipe;

#include "Hoverable.h"
#include "InterfaceSprite.h"
#include "InterfaceText.h"

class ItemRecipeCard :
	public Hoverable,
	public InterfaceDrawable
{
public:
	ItemRecipeCard(
		const ItemRecipe &itemRecipe,
		const sf::Vector2f &size);

	void setPosition(const sf::Vector2f &position);
	void setStatus(bool isCraftable);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	InterfaceSprite productSprite_;
	InterfaceSprite statusSprite_;
	InterfaceText productNameText_;

	bool isCraftable_;

	void updateStatusSpriteOrigin_();
};