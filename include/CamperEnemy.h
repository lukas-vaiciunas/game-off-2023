#pragma once

class Coordinate;
template<typename, typename> class Partition;

#include "Enemy.h"
#include <unordered_map>

class CamperEnemy : public Enemy
{
public:
	CamperEnemy(
		Partition<CamperEnemy, std::unordered_multimap<Coordinate, CamperEnemy *>> &partition,
		const sf::Vector2u &coordinates,
		float speed,
		TextureId animationTextureId,
		TextureId helmetTextureId,
		TextureId chestplateTextureId,
		uint64_t health,
		uint64_t damage,
		float attackRadius,
		float attackSecs);
private:
	Partition<CamperEnemy, std::unordered_multimap<Coordinate, CamperEnemy *>> &partition_;

	float attackRadius_;

	void updateIdle_(const sf::Vector2u &targetCoordinate) override;

	void findNextStep(
		const sf::Vector2u &targetCoordinate,
		const Map &map,
		float manhattanDistance) override;

	void onDeath_() override;
};