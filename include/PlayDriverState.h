#pragma once

#include "DriverState.h"
#include "Player.h"
#include "Map.h"
#include "TileSelector.h"
#include "Camera.h"
#include "hunterEnemySpawner.h"
#include "Eyeball.h"
#include "Equipment.h"
#include "Inventory.h"
#include "InventoryInterface.h"
#include "Crafting.h"
#include "CraftingInterface.h"
#include "HealthInterface.h"
#include "FadingTextPool.h"
#include "ParticlePool.h"

class PlayDriverState : public DriverState
{
public:
	PlayDriverState();

	void update(float deltaTime) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMouseWheelScroll(float delta) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button) override;
	void updateOnMouseButtonRelease(sf::Mouse::Button button) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;

	void draw(
		sf::RenderTarget &target,
		sf::RenderStates states) const override;
private:
	Player player_;
	Map map_;
	TileSelector tileSelector_;
	Camera camera_;

	HunterEnemySpawner hunterEnemySpawner_;

	Eyeball eyeball_;

	Equipment equipment_;
	
	Inventory inventory_;
	InventoryInterface inventoryInterface_;

	Crafting crafting_;
	CraftingInterface craftingInterface_;

	HealthInterface healthInterface_;

	FadingTextPool fadingTextPool_;
	ParticlePool particlePool_;
};