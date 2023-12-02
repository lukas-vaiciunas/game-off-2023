#pragma once

class Inventory;
class Crafting;

#include "Scrollable.h"
#include "ItemRecipeCard.h"
#include <SFML/Window/Mouse.hpp>

class ItemRecipeCardScroller :
	public Scrollable,
	public InterfaceDrawable
{
public:
	ItemRecipeCardScroller(
		const sf::Vector2f &position,
		float width,
		const Crafting &crafting,
		const Inventory &inventory);

	void updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition);
	void updateOnMouseButtonPress(sf::Mouse::Button button);

	void updateItemRecipeCards(
		const Crafting &crafting,
		const Inventory &inventory);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	std::vector<ItemRecipeCard> itemRecipeCards_;

	sf::Vector2f position_;
	float width_;

	void initializeItemRecipeCards_(
		const Crafting &crafting,
		const Inventory &inventory);

	void updateObjectPositions_() override;
};