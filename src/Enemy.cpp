#include "Enemy.h"
#include "Map.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"
#include "PathFinder.h"
#include "Config.h"
#include "Constants.h"

Enemy::Enemy(
	const sf::Vector2u &coordinate,
	float speed,
	TextureId animationTextureId,
	TextureId helmetTextureId,
	TextureId chestplateTextureId,
	uint64_t health,
	uint64_t damage,
	float attackSecs)
	:
	Character(
		coordinate,
		speed,
		TextureData::getInstance().getTexture(
			animationTextureId)),
	state_(State::Idle),
	attackClock_(attackSecs),
	canAttack_(true),
	health_(health),
	damage_(damage),
	isLive_(true)
{
	this->setHelmetTexture_(helmetTextureId);
	this->setChestplateTexture_(chestplateTextureId);
}

void Enemy::updateCombat(
	float deltaTime,
	const sf::Vector2u &targetCoordinate,
	const Map &map)
{
	if (!canAttack_)
	{
		attackClock_.update(deltaTime);

		if (attackClock_.isDone())
		{
			attackClock_.resetSoft();
			canAttack_ = true;
		}
	}

	switch (state_)
	{
		case State::Idle:
			this->updateIdle_(targetCoordinate);
			break;
		case State::Moving:
			this->updateMoving_(deltaTime, targetCoordinate, map);
			break;
		case State::Attacking:
			this->updateAttacking_(targetCoordinate);
			break;
	}
}

void Enemy::hurt(uint64_t damage) // TODO maybe make this part of Character
{
	EventQueue &eventQueue = EventQueue::getInstance();

	if (damage >= health_)
	{
		health_ = 0;

		this->onDeath_();
	}
	else
	{
		health_ -= damage;
	}

	eventQueue.send( // TODO send different sound if 0 damage
		new EventPlaySound(
			3));

	eventQueue.send(
		new EventSpawnFloatingEmphasisText(
			sf::Vector2f(
				coordinate_.x + 0.5f,
				coordinate_.y - 0.25f) * static_cast<float>(Constants::tileSize),
			sf::Vector2f(0.0f, -8.0f),
			std::to_string(damage),
			(damage > 0
				? sf::Color(208, 112, 112)
				: sf::Color(104, 136, 204)),
			Config::Text::Size::medium,
			1.25f));
}

bool Enemy::isLive() const
{
	return isLive_;
}

void Enemy::updateMoving_(
	float deltaTime,
	const sf::Vector2u &targetCoordinate,
	const Map &map)
{
	const float manhattanDistance = PathFinder::getManhattanDistance(coordinate_, targetCoordinate);

	if (manhattanDistance <= 1.0f)
	{
		if (canAttack_)
		{
			this->attack_();
		}
	}

	const sf::Vector2f targetPosition(
		sf::Vector2f(
			coordinate_.x + 0.5f,
			coordinate_.y + 0.5f)
		* static_cast<float>(Constants::tileSize));

	const sf::Vector2f delta = targetPosition - this->getCenterPosition();

	const float angle = atan2f(delta.y, delta.x);

	const sf::Vector2f velocity(
		sf::Vector2f(
			speed_ * cosf(angle),
			speed_ * sinf(angle))
		* deltaTime);

	const float distanceSq = delta.x * delta.x + delta.y * delta.y;
	const float velocitySq = velocity.x * velocity.x + velocity.y * velocity.y;

	if (distanceSq <= velocitySq)
	{
		this->updateSpritePosition_();

		this->findNextStep(targetCoordinate, map, manhattanDistance);
	}
	else
	{
		animation_.move(velocity);

		this->updateHelmetPosition_();
		this->updateChestplatePosition_();
	}
}

void Enemy::updateAttacking_(const sf::Vector2u &targetCoordinate)
{
	if (canAttack_)
	{
		this->attack_();
	}

	if (PathFinder::getManhattanDistance(coordinate_, targetCoordinate) != 1.0f)
	{
		this->changeState_(State::Moving);
	}
}

void Enemy::attack_()
{
	canAttack_ = false;

	EventQueue::getInstance().send(
		new EventHurtPlayer(
			damage_));
}

void Enemy::onDeath_()
{
	const sf::Vector2f &centerPosition = this->getCenterPosition();

	EventQueue &eventQueue = EventQueue::getInstance();

	eventQueue.send(
		new EventSpawnDeathParticles(
			centerPosition,
			centerPosition.y + this->getSize().y * 0.5f));

	eventQueue.send(
		new EventPlaySound(
			101));

	isLive_ = false;
}

void Enemy::changeState_(State state)
{
	if (state_ == state)
	{
		return;
	}

	state_ = state;

	switch (state_)
	{
		case State::Idle:
		case State::Attacking:
			animation_.setRow(0);
			break;
		case State::Moving:
			animation_.setRow(1);
			break;
	}
}