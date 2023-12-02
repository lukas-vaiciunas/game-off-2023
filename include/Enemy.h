#pragma once

class Map;

#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(
		const sf::Vector2u &coordinate,
		float speed,
		TextureId animationTextureId,
		TextureId helmetTextureId,
		TextureId chestplateTextureId,
		uint64_t health,
		uint64_t damage,
		float attackSecs);

	virtual ~Enemy() = default;

	void updateCombat(
		float deltaTime,
		const sf::Vector2u &targetCoordinate,
		const Map &map);

	void hurt(uint64_t damage);

	bool isLive() const;
protected:
	enum class State
	{
		Idle,
		Moving,
		Attacking
	};

	State state_;

	AlarmClock attackClock_;
	bool canAttack_;

	uint64_t health_;
	uint64_t damage_;

	bool isLive_;

	virtual void updateIdle_(const sf::Vector2u &targetCoordinate) {}

	void updateMoving_(
		float deltaTime,
		const sf::Vector2u &targetCoordinate,
		const Map &map);

	void updateAttacking_(const sf::Vector2u &targetCoordinate);

	void attack_();

	virtual void findNextStep(
		const sf::Vector2u &targetCoordinate,
		const Map &map,
		float manhattanDistance) = 0;

	virtual void onDeath_();

	void changeState_(State state);
};