#include "HarvestPlayerState.h"
#include "Player.h"
#include "ResourceNode.h"
#include "Event.h"
#include "EventQueue.h"
#include "Config.h"

HarvestPlayerState::HarvestPlayerState(
	Player &player,
	ResourceNode *resourceNode)
	:
	PlayerState(player),
	resourceNode_(resourceNode),
	power_(nullptr)
{
	switch (resourceNode_->getResourceType())
	{
		case ResourceType::Wood:
			power_ = &player_.axePower_;
			break;
		case ResourceType::Stone:
			power_ = &player_.pickaxePower_;
			break;
	}

	if (!this->checkPowerRequirement_())
	{
		return;
	}

	if (resourceNode_->isEmpty())
	{
		this->stop_();

		return;
	}

	player_.animation_.setRow(0);
}

void HarvestPlayerState::update(float deltaTime)
{
	if (!resourceNode_->updateHarvest(deltaTime, *power_))
	{
		if (this->checkPowerRequirement_())
		{
			return;
		}

		this->stop_();
	}
}

bool HarvestPlayerState::checkPowerRequirement_() const
{
	if (power_ && *power_ >= resourceNode_->getRequiredPower())
	{
		return true;
	}

	EventQueue::getInstance().send(
		new EventSpawnPlayerFloatingText(
			sf::Vector2f(0.0f, -8.0f),
			"Not enough power!",
			sf::Color(208, 112, 112),
			Config::Text::Size::medium,
			1.25f));

	this->stop_();

	return false;
}

void HarvestPlayerState::stop_() const
{
	EventQueue::getInstance().send(
		new EventStopPlayer());
}