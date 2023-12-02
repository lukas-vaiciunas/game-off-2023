#include "MoveAndHarvestPlayerState.h"
#include "Event.h"
#include "EventQueue.h"

MoveAndHarvestPlayerState::MoveAndHarvestPlayerState(
	Player &player,
	const std::stack<sf::Vector2u> &path,
	ResourceNode *resourceNode)
	:
	MovePlayerState(player, path),
	resourceNode_(resourceNode)
{}

void MoveAndHarvestPlayerState::onArrival_()
{
	EventQueue::getInstance().send(
		new EventHarvest(
			resourceNode_));
}