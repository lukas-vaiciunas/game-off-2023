#pragma once

class Map;
class ResourceNode;
class Enemy;
class CamperEnemy;
class HunterEnemy;

#include "DriverStateType.h"
#include "EventType.h"
#include "SoundId.h"
#include "ItemId.h"
#include "TextureId.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

class Event
{
public:
	Event(EventType type) :
		type_(type)
	{}

	virtual ~Event() = default;

	EventType getType() const
	{
		return type_;
	}
private:
	EventType type_;
};

class EventChangeDriverState : public Event
{
public:
	EventChangeDriverState(DriverStateType driverStateType) :
		Event(EventType::ChangeDriverState),
		driverStateType_(driverStateType)
	{}

	DriverStateType getDriverStateType() const
	{
		return driverStateType_;
	}
private:
	DriverStateType driverStateType_;
};

class EventQuit : public Event
{
public:
	EventQuit() :
		Event(EventType::Quit)
	{}
};

class EventPlaySound : public Event
{
public:
	EventPlaySound(SoundId soundId) :
		Event(EventType::PlaySound),
		soundId_(soundId)
	{}

	SoundId getSoundId() const
	{
		return soundId_;
	}
private:
	SoundId soundId_;
};

class EventOpenEyeball : public Event
{
public:
	EventOpenEyeball(const std::string &textString) :
		Event(EventType::OpenEyeball),
		textString_(textString)
	{}

	const std::string &getTextString() const
	{
		return textString_;
	}
private:
	std::string textString_;
};

class EventCloseEyeball : public Event
{
public:
	EventCloseEyeball() :
		Event(EventType::CloseEyeball)
	{}
};

class EventCamperEnemyDeath : public Event
{
public:
	EventCamperEnemyDeath(CamperEnemy *camperEnemy) :
		Event(EventType::CamperEnemyDeath),
		camperEnemy_(camperEnemy)
	{}

	CamperEnemy *getCamperEnemy() const
	{
		return camperEnemy_;
	}
private:
	CamperEnemy *camperEnemy_;
};

class EventHealPlayer : public Event
{
public:
	EventHealPlayer(uint64_t health) :
		Event(EventType::HealPlayer),
		health_(health)
	{}

	uint64_t getHealth() const
	{
		return health_;
	}
private:
	uint64_t health_;
};

class EventHurtPlayer : public Event
{
public:
	EventHurtPlayer(uint64_t damage) :
		Event(EventType::HurtPlayer),
		damage_(damage)
	{}

	uint64_t getDamage() const
	{
		return damage_;
	}
private:
	uint64_t damage_;
};

class EventAddItem : public Event
{
public:
	EventAddItem(ItemId itemId, uint64_t amount) :
		Event(EventType::AddItem),
		itemId_(itemId),
		amount_(amount)
	{}

	ItemId getItemId() const
	{
		return itemId_;
	}

	uint64_t getAmount() const
	{
		return amount_;
	}
private:
	ItemId itemId_;
	uint64_t amount_;
};

class EventRemoveItem : public Event
{
public:
	EventRemoveItem(ItemId itemId, uint64_t amount) :
		Event(EventType::RemoveItem),
		itemId_(itemId),
		amount_(amount)
	{}

	ItemId getItemId() const
	{
		return itemId_;
	}

	uint64_t getAmount() const
	{
		return amount_;
	}
private:
	ItemId itemId_;
	uint64_t amount_;
};

class EventEquipItem : public Event
{
public:
	EventEquipItem(ItemId itemId) :
		Event(EventType::EquipItem),
		itemId_(itemId)
	{}

	ItemId getItemId() const
	{
		return itemId_;
	}
private:
	ItemId itemId_;
};

class EventDequipItem : public Event
{
public:
	EventDequipItem(ItemId itemId) :
		Event(EventType::DequipItem),
		itemId_(itemId)
	{}

	ItemId getItemId() const
	{
		return itemId_;
	}
private:
	ItemId itemId_;
};

class EventChangePlayerWeapon : public Event
{
public:
	EventChangePlayerWeapon(ItemId itemId) :
		Event(EventType::ChangePlayerWeapon),
		itemId_(itemId)
	{}

	ItemId getItemId() const
	{
		return itemId_;
	}
private:
	ItemId itemId_;
};

class EventChangePlayerHelmet : public Event
{
public:
	EventChangePlayerHelmet(ItemId itemId) :
		Event(EventType::ChangePlayerHelmet),
		itemId_(itemId)
	{}

	ItemId getItemId() const
	{
		return itemId_;
	}
private:
	ItemId itemId_;
};

class EventChangePlayerChestplate : public Event
{
public:
	EventChangePlayerChestplate(ItemId itemId) :
		Event(EventType::ChangePlayerChestplate),
		itemId_(itemId)
	{}

	ItemId getItemId() const
	{
		return itemId_;
	}
private:
	ItemId itemId_;
};

class EventChangePlayerAxe : public Event
{
public:
	EventChangePlayerAxe(ItemId itemId) :
		Event(EventType::ChangePlayerAxe),
		itemId_(itemId)
	{}

	ItemId getItemId() const
	{
		return itemId_;
	}
private:
	ItemId itemId_;
};

class EventChangePlayerPickaxe : public Event
{
public:
	EventChangePlayerPickaxe(ItemId itemId) :
		Event(EventType::ChangePlayerPickaxe),
		itemId_(itemId)
	{}

	ItemId getItemId() const
	{
		return itemId_;
	}
private:
	ItemId itemId_;
};

class EventHarvest : public Event
{
public:
	EventHarvest(ResourceNode *resourceNode) :
		Event(EventType::Harvest),
		resourceNode_(resourceNode)
	{}

	ResourceNode *getResourceNode() const
	{
		return resourceNode_;
	}
private:
	ResourceNode *resourceNode_;
};

class EventMovePlayerAndHarvest : public Event
{
public:
	EventMovePlayerAndHarvest(
		const sf::Vector2u &coordinates,
		const Map &map)
		:
		Event(EventType::MovePlayerAndHarvest),
		map_(map),
		coordinates_(coordinates)
	{}

	const Map &getMap() const
	{
		return map_;
	}

	const sf::Vector2u &getCoordinates() const
	{
		return coordinates_;
	}
private:
	const Map &map_;
	sf::Vector2u coordinates_;
};

class EventAttack : public Event
{
public:
	EventAttack(Enemy *enemy) :
		Event(EventType::Attack),
		enemy_(enemy)
	{}

	Enemy *getEnemy() const
	{
		return enemy_;
	}
private:
	Enemy *enemy_;
};

class EventMovePlayerAndAttack : public Event
{
public:
	EventMovePlayerAndAttack(Enemy *enemy, const Map &map) :
		Event(EventType::MovePlayerAndAttack),
		map_(map),
		enemy_(enemy)
	{}

	Enemy *getEnemy() const
	{
		return enemy_;
	}

	const Map &getMap() const
	{
		return map_;
	}
private:
	const Map &map_;
	Enemy *enemy_;
};

class EventMovePlayer : public Event
{
public:
	EventMovePlayer(
		const sf::Vector2u &coordinates,
		const Map &map)
		:
		Event(EventType::MovePlayer),
		map_(map),
		coordinates_(coordinates)
	{}

	const Map &getMap() const
	{
		return map_;
	}

	const sf::Vector2u &getCoordinates() const
	{
		return coordinates_;
	}
private:
	const Map &map_;
	sf::Vector2u coordinates_;
};

class EventStopPlayer : public Event
{
public:
	EventStopPlayer() :
		Event(EventType::StopPlayer)
	{}
};

class EventSpawnHunterEnemy : public Event
{
public:
	EventSpawnHunterEnemy(HunterEnemy *hunterEnemy) :
		Event(EventType::SpawnHunterEnemy),
		hunterEnemy_(hunterEnemy)
	{}

	HunterEnemy *getHunterEnemy() const
	{
		return hunterEnemy_;
	}
private:
	HunterEnemy *hunterEnemy_;
};

class EventSpawnFloatingText : public Event
{
public:
	EventSpawnFloatingText(
		const sf::Vector2f &position,
		const sf::Vector2f &velocity,
		const std::string &string,
		const sf::Color &fillColor,
		unsigned int characterSize,
		float durationSecs)
		:
		Event(EventType::SpawnFloatingText),
		position_(position),
		velocity_(velocity),
		string_(string),
		fillColor_(fillColor),
		characterSize_(characterSize),
		durationSecs_(durationSecs)
	{}

	const sf::Vector2f &getPosition() const
	{
		return position_;
	}

	const sf::Vector2f &getVelocity() const
	{
		return velocity_;
	}

	const std::string &getString() const
	{
		return string_;
	}

	const sf::Color &getFillColor() const
	{
		return fillColor_;
	}

	unsigned int getCharacterSize() const
	{
		return characterSize_;
	}

	float getDurationSecs() const
	{
		return durationSecs_;
	}
private:
	sf::Vector2f position_;
	sf::Vector2f velocity_;
	std::string string_;
	sf::Color fillColor_;
	unsigned int characterSize_;
	float durationSecs_;
};

class EventSpawnPlayerFloatingText : public Event
{
public:
	EventSpawnPlayerFloatingText(
		const sf::Vector2f &velocity,
		const std::string &string,
		const sf::Color &fillColor,
		unsigned int characterSize,
		float durationSecs)
		:
		Event(EventType::SpawnPlayerFloatingText),
		velocity_(velocity),
		string_(string),
		fillColor_(fillColor),
		characterSize_(characterSize),
		durationSecs_(durationSecs)
	{}

	const sf::Vector2f &getVelocity() const
	{
		return velocity_;
	}

	const std::string &getString() const
	{
		return string_;
	}

	const sf::Color &getFillColor() const
	{
		return fillColor_;
	}

	unsigned int getCharacterSize() const
	{
		return characterSize_;
	}

	float getDurationSecs() const
	{
		return durationSecs_;
	}
private:
	sf::Vector2f velocity_;
	std::string string_;
	sf::Color fillColor_;
	unsigned int characterSize_;
	float durationSecs_;
};

class EventSpawnFloatingIconText : public Event
{
public:
	EventSpawnFloatingIconText(
		const sf::Vector2f &position,
		const sf::Vector2f &velocity,
		const std::string &string,
		const sf::Color &fillColor,
		unsigned int characterSize,
		TextureId textureId,
		float durationSecs)
		:
		Event(EventType::SpawnFloatingIconText),
		position_(position),
		velocity_(velocity),
		string_(string),
		fillColor_(fillColor),
		characterSize_(characterSize),
		textureId_(textureId),
		durationSecs_(durationSecs)
	{}

	const sf::Vector2f &getPosition() const
	{
		return position_;
	}

	const sf::Vector2f &getVelocity() const
	{
		return velocity_;
	}

	const std::string &getString() const
	{
		return string_;
	}

	const sf::Color &getFillColor() const
	{
		return fillColor_;
	}

	unsigned int getCharacterSize() const
	{
		return characterSize_;
	}

	ItemId getTextureId() const
	{
		return textureId_;
	}

	float getDurationSecs() const
	{
		return durationSecs_;
	}
private:
	sf::Vector2f position_;
	sf::Vector2f velocity_;
	std::string string_;
	sf::Color fillColor_;
	unsigned int characterSize_;
	TextureId textureId_;
	float durationSecs_;
};

class EventSpawnFloatingEmphasisText : public Event // TODO fix bug somewhere related to pointers
{
public:
	EventSpawnFloatingEmphasisText(
		const sf::Vector2f &position,
		const sf::Vector2f &velocity,
		const std::string &string,
		const sf::Color &fillColor,
		unsigned int characterSize,
		float durationSecs)
		:
		Event(EventType::SpawnFloatingEmphasisText),
		position_(position),
		velocity_(velocity),
		string_(string),
		fillColor_(fillColor),
		characterSize_(characterSize),
		durationSecs_(durationSecs)
	{}

	const sf::Vector2f &getPosition() const
	{
		return position_;
	}

	const sf::Vector2f &getVelocity() const
	{
		return velocity_;
	}

	const std::string &getString() const
	{
		return string_;
	}

	const sf::Color &getFillColor() const
	{
		return fillColor_;
	}

	unsigned int getCharacterSize() const
	{
		return characterSize_;
	}

	float getDurationSecs() const
	{
		return durationSecs_;
	}
private:
	sf::Vector2f position_;
	sf::Vector2f velocity_;
	std::string string_;
	sf::Color fillColor_;
	unsigned int characterSize_;
	float durationSecs_;
};

class EventSpawnDeathParticles : public Event
{
public:
	EventSpawnDeathParticles(
		const sf::Vector2f &position,
		float floorY)
		:
		Event(EventType::SpawnDeathParticles),
		position_(position),
		floorY_(floorY)
	{}

	const sf::Vector2f &getPosition() const
	{
		return position_;
	}

	float getFloorY() const
	{
		return floorY_;
	}
private:
	sf::Vector2f position_;
	float floorY_;
};

class EventUpdateInventoryInterface : public Event
{
public:
	EventUpdateInventoryInterface() :
		Event(EventType::UpdateInventoryInterface)
	{}
};

class EventUpdateCraftingInterface : public Event
{
public:
	EventUpdateCraftingInterface() :
		Event(EventType::UpdateCraftingInterface)
	{}
};

class EventUpdateHealthInterface : public Event
{
public:
	EventUpdateHealthInterface(float fillRatio) :
		Event(EventType::UpdateHealthInterface),
		fillRatio_(fillRatio)
	{}

	float getFillRatio() const
	{
		return fillRatio_;
	}
private:
	float fillRatio_;
};

class EventViewCraftingList : public Event
{
public:
	EventViewCraftingList() :
		Event(EventType::ViewCraftingList)
	{}
};

class EventViewCraftingItem : public Event
{
public:
	EventViewCraftingItem(size_t itemRecipeIndex) :
		Event(EventType::ViewCraftingItem),
		itemRecipeIndex_(itemRecipeIndex)
	{}

	size_t getItemRecipeIndex() const
	{
		return itemRecipeIndex_;
	}
private:
	size_t itemRecipeIndex_;
};