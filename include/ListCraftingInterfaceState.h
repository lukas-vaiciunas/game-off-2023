#pragma once

#include "CraftingInterfaceState.h"
#include "ItemRecipeCardScroller.h"
#include "TextButton.h"

class ListCraftingInterfaceState : public CraftingInterfaceState
{
public:
	ListCraftingInterfaceState(CraftingInterface &parent);

	void updateOnEvent() override;
	void update(float deltaTime) override;
	void updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition) override;
	void updateOnMouseWheelScroll(float delta) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button) override;
	void updateOnMouseButtonRelease(sf::Mouse::Button button) override;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	ItemRecipeCardScroller itemRecipeCardScroller_;

	TextButton closeButton_;
};