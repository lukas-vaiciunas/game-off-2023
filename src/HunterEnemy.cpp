#include "HunterEnemy.h"
#include "Map.h"
#include "PathFinder.h"

HunterEnemy::HunterEnemy(
	const sf::Vector2u &coordinate,
	float speed,
	TextureId animationTextureId,
	TextureId helmetTextureId,
	TextureId chestplateTextureId,
	uint64_t health,
	uint64_t damage,
	float attackSecs)
	:
	Enemy(
		coordinate,
		speed,
		animationTextureId,
		helmetTextureId,
		chestplateTextureId,
		health,
		damage,
		attackSecs)
{
	this->changeState_(State::Moving);
}

void HunterEnemy::findNextStep(
	const sf::Vector2u &targetCoordinate,
	const Map &map,
	float manhattanDistance)
{
	if (manhattanDistance == 1.0f)
	{
		this->changeState_(State::Attacking);
	}
	else
	{
		const std::stack<sf::Vector2u> path = std::move(
			PathFinder::findPath(
				coordinate_,
				map.getClosestCoordinate(
					coordinate_,
					map.getNavigableAdjacents(targetCoordinate)),
				map));

		if (path.empty())
		{
			this->changeState_(State::Attacking);
		}
		else
		{
			coordinate_ = path.top();
		}
	}
}