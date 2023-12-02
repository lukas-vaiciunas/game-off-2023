#include "AttackPlayerState.h"
#include "Player.h"
#include "Enemy.h"
#include "Event.h"
#include "EventQueue.h"

AttackPlayerState::AttackPlayerState(Player &player, Enemy *enemy) :
	PlayerState(player),
	enemy_(enemy)
{
	player_.animation_.setRow(0);
}

void AttackPlayerState::update(float deltaTime)
{
	if (player_.canAttack_)
	{
		player_.attack_(*enemy_); // TODO check if player leaves attack player state upon killing enemy

		if (!enemy_->isLive())
		{
			EventQueue::getInstance().send(
				new EventStopPlayer());
		}
	}
}