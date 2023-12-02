#pragma once

class Enemy;
class Map;

#include "PlayerState.h"

class MoveAndAttackPlayerState : public PlayerState
{
public:
	MoveAndAttackPlayerState(Player &player, Enemy *enemy, const Map &map);

	void update(float deltaTime) override;
private:
	const Map &map_;
	Enemy *enemy_;
};