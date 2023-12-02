#pragma once

#include "PanelInterface.h"
#include "Listener.h"
#include "ItemCardScroller.h"
#include "TextButton.h"

class InventoryInterface :
	public PanelInterface,
	public Listener
{
public:
	InventoryInterface(
		const sf::Vector2f &centerPosition,
		const Inventory &inventory,
		const Equipment &equipment);

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
	const Inventory &inventory_;
	const Equipment &equipment_;

	ItemCardScroller itemCardScroller_;

	TextButton closeButton_;
};