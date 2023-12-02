#include "ItemCardScroller.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Event.h"
#include "EventQueue.h"
#include "FoodItem.h"
#include "ItemData.h"

ItemCardScroller::ItemCardScroller(
	const sf::Vector2f &position,
	float width)
	:
	Scrollable(6),
	InterfaceDrawable(),
	itemCards_(),
	position_(position),
	width_(width)
{}

void ItemCardScroller::updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition)
{
	for (uint64_t i = 0; i < numObjectsDisplayed_; ++i)
	{
		itemCards_[scrollIndex_ + i].updateOnMouseMove(mouseInterfacePosition);
	}
}

void ItemCardScroller::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	for (uint64_t i = 0; i < numObjectsDisplayed_; ++i)
	{
		const ItemCard &itemCard = itemCards_[scrollIndex_ + i];

		if (!itemCard.isHovered())
		{
			continue;
		}

		EventQueue &eventQueue = EventQueue::getInstance();

		ItemId itemId = itemCard.getItemId();
		const Item *item = ItemData::getInstance().getItem(itemId);
		Item::Type itemType = item->getType();

		switch (itemType)
		{
			case Item::Type::Food:
				eventQueue.send(
					new EventRemoveItem(
						itemId, 1));
				eventQueue.send(
					new EventHealPlayer(
						static_cast<const FoodItem *>(item)->getNutrition()));
				eventQueue.send(
					new EventPlaySound(
						301));
				break;
			case Item::Type::Weapon:
			case Item::Type::Helmet:
			case Item::Type::Chestplate:
			case Item::Type::Axe:
			case Item::Type::Pickaxe:
				eventQueue.send(
					new EventEquipItem(
						itemId));
				break;
		}

		break;
	}
}

void ItemCardScroller::updateItemCards(
	const Inventory &inventory,
	const Equipment &equipment)
{
	const std::map<ItemId, uint64_t> &items = inventory.getItems();
	const std::unordered_set<ItemId> equippedItemIds = std::move(equipment.getEquippedItemIds());

	itemCards_.clear();

	uint64_t row = 0;

	for (auto it = items.begin(); it != items.end(); ++it)
	{
		ItemCard itemCard(
			it->first,
			it->second,
			sf::Vector2f(width_, 8.0f));

		if (equippedItemIds.find(it->first) != equippedItemIds.end())
		{
			itemCard.setEquipped(true);
		}

		itemCards_.emplace_back(std::move(itemCard));

		++row;
	}

	this->setNumObjects_(itemCards_.size());
	this->updateObjectPositions_();
}

void ItemCardScroller::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	for (uint64_t i = 0; i < numObjectsDisplayed_; ++i)
	{
		itemCards_[scrollIndex_ + i].draw(target, states, scale);
	}
}

void ItemCardScroller::updateObjectPositions_()
{
	for (uint64_t i = 0; i < numObjectsDisplayed_; ++i)
	{
		itemCards_[scrollIndex_ + i].setPosition(
			sf::Vector2f(
				position_.x,
				position_.y + 10.0f * i));
	}
}