#include "MoveAndAttackPlayerState.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Event.h"
#include "EventQueue.h"
#include "PathFinder.h"
#include "Constants.h"

MoveAndAttackPlayerState::MoveAndAttackPlayerState(Player &player, Enemy *enemy, const Map &map) :
	PlayerState(player),
	map_(map),
	enemy_(enemy)
{
	player_.animation_.setRow(1);
}

void MoveAndAttackPlayerState::update(float deltaTime)
{
	const float manhattanDistance = PathFinder::getManhattanDistance(
		player_.coordinate_,
		enemy_->getCoordinate());

	if (manhattanDistance <= 1.0f)
	{
		if (player_.canAttack_)
		{
			player_.attack_(*enemy_);
		}
	}

	const sf::Vector2f targetPosition(
		sf::Vector2f(
			player_.coordinate_.x + 0.5f,
			player_.coordinate_.y + 0.5f)
		* static_cast<float>(Constants::tileSize));

	const sf::Vector2f delta = targetPosition - player_.getCenterPosition();

	const float angle = atan2f(delta.y, delta.x);

	const sf::Vector2f velocity(
		sf::Vector2f(
			player_.speed_ * cosf(angle),
			player_.speed_ * sinf(angle))
		* deltaTime);

	const float distanceSq = delta.x * delta.x + delta.y * delta.y;
	const float velocitySq = velocity.x * velocity.x + velocity.y * velocity.y;

	if (distanceSq <= velocitySq)
	{
		player_.updateSpritePosition_();

		if (manhattanDistance == 1.0f)
		{
			if (!enemy_->isLive())
			{
				EventQueue::getInstance().send(
					new EventStopPlayer());
			}
			else
			{
				EventQueue::getInstance().send(
					new EventAttack(
						enemy_));
			}
		}
		else
		{
			const std::stack<sf::Vector2u> path = std::move(
				PathFinder::findPath(
					player_.coordinate_,
					map_.getClosestCoordinate(
						player_.coordinate_,
						map_.getNavigableAdjacents(enemy_->getCoordinate())),
					map_));

			if (path.empty())
			{
				EventQueue::getInstance().send(
					new EventAttack(
						enemy_));
			}
			else
			{
				player_.coordinate_ = path.top();
			}
		}
	}
	else
	{
		player_.animation_.move(velocity);

		player_.updateHelmetPosition_();
		player_.updateChestplatePosition_();
	}

	player_.updateFootstepSounds_();
}