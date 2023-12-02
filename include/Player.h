#pragma once

class PlayerState;
class Enemy;

#include "Character.h"
#include "Listener.h"
#include "ItemId.h"

class Player :
	public Character,
	public Listener
{
public:
	Player(
		const sf::Vector2u &coordinates,
		float speed,
		const sf::Texture &texture);

	~Player();

	void onEvent(const Event &ev) override;

	void update(float deltaTime) override;
private:
	friend class IdlePlayerState;
	friend class MovePlayerState;
	friend class MoveAndAttackPlayerState;
	friend class AttackPlayerState;
	friend class HarvestPlayerState;

	PlayerState *state_;

	uint64_t weaponDamage_;
	uint64_t helmetArmor_;
	uint64_t chestplateArmor_;
	uint8_t axePower_;
	uint8_t pickaxePower_;

	uint64_t maxHealth_;
	uint64_t health_;

	AlarmClock attackClock_;
	bool canAttack_;

	void updateFootstepSounds_();

	void updateAttacking_(float deltaTime);
	void attack_(Enemy &enemy);
	void heal_(uint64_t health);
	void hurt_(uint64_t damage);

	void changeWeapon_(ItemId itemId);
	void changeHelmet_(ItemId itemId);
	void changeChestplate_(ItemId itemId);
	void changeAxe_(ItemId itemId);
	void changePickaxe_(ItemId itemId);
};