#pragma once

#include "Tile.h"
#include "Shakable.h"
#include "ResourceType.h"
#include "TextureId.h"
#include "ItemId.h"
#include "AlarmClock.h"

class ResourceNode :
	public Tile,
	public Shakable
{
public:
	ResourceNode(
		const sf::Vector2u &coordinates,
		TextureId textureId,
		TextureId emptyTextureId,
		ResourceType type,
		ItemId itemId,
		uint64_t numItems,
		uint8_t requiredPower,
		float harvestTime);

	void update(float deltaTime) override;
	bool updateHarvest(float deltaTime, uint8_t power);

	ResourceNode *clone(const sf::Vector2u &coordinates) const;
	
	ResourceType getResourceType() const;
	uint8_t getRequiredPower() const;
	bool isEmpty() const;
private:
	ResourceType type_;
	TextureId textureId_;
	TextureId emptyTextureId_;
	ItemId itemId_;
	uint64_t numItems_;

	uint8_t requiredPower_;

	AlarmClock harvestClock_;

	sf::Vector2f anchorSpritePosition_;

	void playHitSound_();
};