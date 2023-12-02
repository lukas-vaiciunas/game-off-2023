#pragma once

class Enemy;

#include "PlayerState.h"
#include "AlarmClock.h"

class AttackPlayerState : public PlayerState
{
public:
	AttackPlayerState(Player &player, Enemy *enemy);

	void update(float deltaTime) override;
private:
	Enemy *enemy_;
};