#pragma once

#include "Pool.h"
#include "HunterEnemy.h"
#include "Listener.h"

class HunterEnemyPool :
	public Pool<HunterEnemy>,
	public Listener,
	public WorldDrawable
{
public:
	HunterEnemyPool(Size capacity);

	void onEvent(const Event &ev) override;

	void update(float deltaTime);

	void updateCombat(
		float deltaTime,
		const sf::Vector2u &targetCoordinate,
		const Map &map);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
};