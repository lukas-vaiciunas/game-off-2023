#include "IdlePlayerState.h"
#include "Player.h"

IdlePlayerState::IdlePlayerState(Player &player) :
	PlayerState(player)
{
	player_.animation_.setRow(0);
}