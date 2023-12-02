#pragma once

class ResourceNode;

#include "PlayerState.h"
#include <cstdint>

class HarvestPlayerState : public PlayerState
{
public:
	HarvestPlayerState(
		Player &player,
		ResourceNode *resourceNode);

	void update(float deltaTime) override;
private:
	ResourceNode *resourceNode_;
	uint8_t *power_;

	bool checkPowerRequirement_() const;
	void stop_() const;
};