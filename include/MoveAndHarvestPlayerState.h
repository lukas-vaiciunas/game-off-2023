#pragma once

class ResourceNode;

#include "MovePlayerState.h"

class MoveAndHarvestPlayerState : public MovePlayerState
{
public:
	MoveAndHarvestPlayerState(
		Player &player,
		const std::stack<sf::Vector2u> &path,
		ResourceNode *resourceNode);
private:
	ResourceNode *resourceNode_;

	void onArrival_() override;
};