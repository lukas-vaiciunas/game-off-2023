#include "HunterEnemyPool.h"
#include "Event.h"

HunterEnemyPool::HunterEnemyPool(Size capacity) :
	Pool(capacity),
	Listener({ EventType::SpawnHunterEnemy }),
	WorldDrawable()
{}

void HunterEnemyPool::onEvent(const Event &ev)
{
	HunterEnemy *hunterEnemy = static_cast<const EventSpawnHunterEnemy &>(ev).getHunterEnemy();

	if (this->isFull_())
	{
		delete hunterEnemy;
		return;
	}

	this->add_(hunterEnemy);
}

void HunterEnemyPool::update(float deltaTime)
{
	for (Size i = 0; i < numLive_; )
	{
		objects_[i]->update(deltaTime);

		if (!objects_[i]->isLive())
		{
			this->remove_(i);
		}
		else ++i;
	}
}

void HunterEnemyPool::updateCombat(
	float deltaTime,
	const sf::Vector2u &targetCoordinate,
	const Map &map)
{
	for (Size i = 0; i < numLive_; ++i)
	{
		objects_[i]->updateCombat(deltaTime, targetCoordinate, map);
	}
}

void HunterEnemyPool::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	for (Size i = 0; i < numLive_; ++i)
	{
		objects_[i]->draw(target, states, offset, scale);
	}
}