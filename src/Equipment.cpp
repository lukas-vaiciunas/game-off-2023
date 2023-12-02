#include "Equipment.h"
#include "HelmetItem.h"
#include "ItemData.h"
#include "Event.h"
#include "EventQueue.h"

Equipment::Equipment() :
	Listener(
		{
			EventType::EquipItem,
			EventType::DequipItem
		}),
	weaponId_(0),
	helmetId_(0),
	chestplateId_(0),
	axeId_(0),
	pickaxeId_(0)
{}

void Equipment::onEvent(const Event &ev)
{
	switch (ev.getType())
	{
		case EventType::EquipItem:
			this->equipItem_(
				static_cast<const EventEquipItem &>(ev).getItemId());
			break;
		case EventType::DequipItem:
			this->dequipItem_(
				static_cast<const EventDequipItem &>(ev).getItemId());
			break;
	}
}

std::unordered_set<ItemId> Equipment::getEquippedItemIds() const
{
	std::unordered_set<ItemId> equippedItemIds;

	if (weaponId_)
	{
		equippedItemIds.emplace(weaponId_);
	}
	if (helmetId_)
	{
		equippedItemIds.emplace(helmetId_);
	}
	if (chestplateId_)
	{
		equippedItemIds.emplace(chestplateId_);
	}
	if (axeId_)
	{
		equippedItemIds.emplace(axeId_);
	}
	if (pickaxeId_)
	{
		equippedItemIds.emplace(pickaxeId_);
	}

	return equippedItemIds;
}

void Equipment::equipItem_(ItemId itemId)
{
	switch (ItemData::getInstance().getItem(itemId)->getType())
	{
		case Item::Type::Weapon:
			this->equipWeapon_(itemId);
			break;
		case Item::Type::Helmet:
			this->equipHelmet_(itemId);
			break;
		case Item::Type::Chestplate:
			this->equipChestplate_(itemId);
			break;
		case Item::Type::Axe:
			this->equipAxe_(itemId);
			break;
		case Item::Type::Pickaxe:
			this->equipPickaxe_(itemId);
			break;
	}

	EventQueue::getInstance().send(
		new EventPlaySound(
			303));
}

void Equipment::equipWeapon_(ItemId itemId)
{
	weaponId_ = (weaponId_ == itemId ? 0 : itemId);

	EventQueue::getInstance().send(
		new EventChangePlayerWeapon(
			weaponId_));

	this->sendUpdates_();
}

void Equipment::equipHelmet_(ItemId itemId)
{
	helmetId_ = (helmetId_ == itemId ? 0 : itemId);

	EventQueue::getInstance().send(
		new EventChangePlayerHelmet(
			helmetId_));

	this->sendUpdates_();
}

void Equipment::equipChestplate_(ItemId itemId)
{
	chestplateId_ = (chestplateId_ == itemId ? 0 : itemId);

	EventQueue::getInstance().send(
		new EventChangePlayerChestplate(
			chestplateId_));

	this->sendUpdates_();
}

void Equipment::equipAxe_(ItemId itemId)
{
	axeId_ = (axeId_ == itemId ? 0 : itemId);

	EventQueue::getInstance().send(
		new EventChangePlayerAxe(
			axeId_));

	this->sendUpdates_();
}

void Equipment::equipPickaxe_(ItemId itemId)
{
	pickaxeId_ = (pickaxeId_ == itemId ? 0 : itemId);

	EventQueue::getInstance().send(
		new EventChangePlayerPickaxe(
			pickaxeId_));

	this->sendUpdates_();
}

void Equipment::dequipItem_(ItemId itemId)
{
	if (weaponId_ == itemId)
	{
		this->equipWeapon_(0);
	}
	else if (helmetId_ == itemId)
	{
		this->equipHelmet_(0);
	}
	else if (chestplateId_ == itemId)
	{
		this->equipChestplate_(0);
	}
	else if (axeId_ == itemId)
	{
		this->equipAxe_(0);
	}
	else if (pickaxeId_ == itemId)
	{
		this->equipPickaxe_(0);
	}
}

void Equipment::sendUpdates_() const
{
	EventQueue::getInstance().send(
		new EventUpdateInventoryInterface());
}