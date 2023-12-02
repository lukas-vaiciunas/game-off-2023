#pragma once

class Crafting;
class Inventory;
class CraftingInterfaceState;

#include "PanelInterface.h"
#include "Listener.h"
#include <SFML/Window/Mouse.hpp>

class CraftingInterface :
	public PanelInterface,
	public Listener
{
public:
	CraftingInterface(
		const sf::Vector2f &centerPosition,
		const Crafting &crafting,
		const Inventory &inventory);

	~CraftingInterface();

	void onEvent(const Event &ev) override;

	void update(float deltaTime);
	void updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition) override;
	void updateOnMouseWheelScroll(float delta);
	void updateOnMouseButtonPress(sf::Mouse::Button button);
	void updateOnMouseButtonRelease(sf::Mouse::Button button);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	friend class ListCraftingInterfaceState;
	friend class ItemCraftingInterfaceState;

	const Crafting &crafting_;
	const Inventory &inventory_;

	CraftingInterfaceState *state_;
};