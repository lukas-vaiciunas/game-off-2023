#include "CamperEnemy.h"
#include "Map.h"
#include "Event.h"
#include "EventQueue.h"
#include "PathFinder.h"

CamperEnemy::CamperEnemy(
	Partition<CamperEnemy, std::unordered_multimap<Coordinate, CamperEnemy *>> &partition,
	const sf::Vector2u &coordinates,
	float speed,
	TextureId animationTextureId,
	TextureId helmetTextureId,
	TextureId chestplateTextureId,
	uint64_t health,
	uint64_t damage,
	float attackRadius,
	float attackSecs)
	:
	Enemy(
		coordinates,
		speed,
		animationTextureId,
		helmetTextureId,
		chestplateTextureId,
		health,
		damage,
		attackSecs),
	partition_(partition),
	attackRadius_(attackRadius)
{}

void CamperEnemy::updateIdle_(const sf::Vector2u &targetCoordinate)
{
	if (PathFinder::getEuclideanDistance(coordinate_, targetCoordinate) <= attackRadius_)
	{
		this->changeState_(
			(PathFinder::getManhattanDistance(coordinate_, targetCoordinate) <= 1.0f
				? State::Moving
				: State::Attacking));
	}
}

void CamperEnemy::findNextStep(
	const sf::Vector2u &targetCoordinate,
	const Map &map,
	float manhattanDistance)
{
	if (PathFinder::getEuclideanDistance(coordinate_, targetCoordinate) > attackRadius_)
	{
		this->changeState_(State::Idle);
	}
	else if (manhattanDistance == 1.0f)
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
			partition_.remove(this);

			coordinate_ = path.top();

			partition_.add(this);
		}
	}
}

void CamperEnemy::onDeath_()
{
	Enemy::onDeath_();

	EventQueue::getInstance().send(
		new EventCamperEnemyDeath(
			this));
}