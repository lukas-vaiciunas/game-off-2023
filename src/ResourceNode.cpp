#include "ResourceNode.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"

ResourceNode::ResourceNode(
	const sf::Vector2u &coordinates,
	TextureId textureId,
	TextureId emptyTextureId,
	ResourceType type,
	ItemId itemId,
	uint64_t numItems,
	uint8_t requiredPower,
	float harvestTime)
	:
	Tile(
		coordinates,
		TextureData::getInstance().getTexture(
			textureId)),
	Shakable(1.0f, 0.9f),
	type_(type),
	textureId_(textureId),
	emptyTextureId_(emptyTextureId),
	itemId_(itemId),
	numItems_(numItems),
	requiredPower_(requiredPower),
	harvestClock_(harvestTime),
	anchorSpritePosition_(sprite_.getPosition())
{}

void ResourceNode::update(float deltaTime)
{
	Shakable::update(deltaTime);

	sprite_.setPosition(anchorSpritePosition_ + offset_);
}

bool ResourceNode::updateHarvest(float deltaTime, uint8_t power)
{
	if (numItems_ == 0)
	{
		return false;
	}

	harvestClock_.update(deltaTime);

	if (harvestClock_.isDone())
	{
		harvestClock_.resetSoft();

		if (power < requiredPower_)
		{
			return false;
		}

		uint64_t amount = power - requiredPower_ + 1;

		if (amount > numItems_)
		{
			amount = numItems_;
		}

		numItems_ -= amount;

		if (numItems_ == 0)
		{
			sprite_.setTexture(
				TextureData::getInstance().getTexture(
					emptyTextureId_));

			if (type_ == ResourceType::Wood)
			{
				EventQueue::getInstance().send(
					new EventAddItem(
						451,
						1));
			}
		}

		EventQueue::getInstance().send(
			new EventAddItem(
				itemId_,
				amount));

		this->playHitSound_();

		this->shake_(1.0f);
	}

	return true;
}

ResourceNode *ResourceNode::clone(const sf::Vector2u &coordinates) const
{
	return new ResourceNode(
		coordinates,
		textureId_,
		emptyTextureId_,
		type_,
		itemId_,
		numItems_,
		requiredPower_,
		harvestClock_.getTargetSecs());
}

ResourceType ResourceNode::getResourceType() const
{
	return type_;
}

uint8_t ResourceNode::getRequiredPower() const
{
	return requiredPower_;
}

bool ResourceNode::isEmpty() const
{
	return numItems_ == 0;
}

void ResourceNode::playHitSound_()
{
	SoundId soundId = 0;

	switch (type_)
	{
		case ResourceType::Wood:
			soundId = 1;
			break;
		case ResourceType::Stone:
			soundId = 2;
			break;
	}

	if (soundId == 0)
	{
		return;
	}

	EventQueue::getInstance().send(
		new EventPlaySound(
			soundId));
}