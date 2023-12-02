#pragma once

class Inventory;
class Equipment;

#include "Scrollable.h"
#include "ItemCard.h"
#include <SFML/Window/Mouse.hpp>

class ItemCardScroller :
	public Scrollable,
	public InterfaceDrawable
{
public:
	ItemCardScroller(
		const sf::Vector2f &position,
		float width);

	void updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition);
	void updateOnMouseButtonPress(sf::Mouse::Button button);

	void updateItemCards(
		const Inventory &inventory,
		const Equipment &equipment);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	std::vector<ItemCard> itemCards_;

	sf::Vector2f position_;
	float width_;

	void updateObjectPositions_() override;
};