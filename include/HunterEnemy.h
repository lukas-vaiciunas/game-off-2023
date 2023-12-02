#pragma once

#include "Enemy.h"

class HunterEnemy : public Enemy
{
public:
	HunterEnemy(
		const sf::Vector2u &coordinate,
		float speed,
		TextureId animationTextureId,
		TextureId helmetTextureId,
		TextureId chestplateTextureId,
		uint64_t health,
		uint64_t damage,
		float attackSecs);
private:
	void findNextStep(
		const sf::Vector2u &targetCoordinate,
		const Map &map,
		float manhattanDistance) override;
};