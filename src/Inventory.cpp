#include "Inventory.h"
#include "Equipment.h"
#include "Event.h"
#include "EventQueue.h"

Inventory::Inventory(const Equipment &equipment) :
	Listener(
		{
			EventType::AddItem,
			EventType::RemoveItem
		}),
	equipment_(equipment),
	items_()
{}

void Inventory::onEvent(const Event &ev)
{
	switch (ev.getType())
	{
		case EventType::AddItem:
		{
			const EventAddItem &eventAddItem = static_cast<const EventAddItem &>(ev);

			this->addItem_(
				eventAddItem.getItemId(),
				eventAddItem.getAmount());

			break;
		}	
		case EventType::RemoveItem:
		{
			const EventRemoveItem &eventRemoveItem = static_cast<const EventRemoveItem &>(ev);

			this->removeItem_(
				eventRemoveItem.getItemId(),
				eventRemoveItem.getAmount());

			break;
		}
	}
}

bool Inventory::contains(ItemId itemId, uint64_t amount) const
{
	auto it = items_.find(itemId);

	return it != items_.end() && it->second >= amount;
}

const std::map<ItemId, uint64_t> &Inventory::getItems() const
{
	return items_;
}

void Inventory::addItem_(ItemId itemId, uint64_t amount)
{
	auto it = items_.find(itemId);

	if (it == items_.end())
	{
		items_.emplace(itemId, amount);
	}
	else
	{
		it->second += amount;
	}

	this->sendUpdates_();
}

void Inventory::removeItem_(ItemId itemId, uint64_t amount)
{
	auto it = items_.find(itemId);

	if (it == items_.end())
	{
		return;
	}

	if (it->second <= amount)
	{
		const std::unordered_set<ItemId> equippedItemIds = std::move(equipment_.getEquippedItemIds());

		if (equippedItemIds.find(it->first) != equippedItemIds.end())
		{
			EventQueue::getInstance().send(
				new EventDequipItem(
					it->first));
		}

		items_.erase(it);
	}
	else
	{
		it->second -= amount;
	}

	this->sendUpdates_();
}

void Inventory::sendUpdates_() const
{
	EventQueue::getInstance().send(
		new EventUpdateInventoryInterface());

	EventQueue::getInstance().send(
		new EventUpdateCraftingInterface());
}