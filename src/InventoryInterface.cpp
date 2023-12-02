#include "InventoryInterface.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Item.h"
#include "ItemData.h"
#include "Event.h"
#include "EventQueue.h"
#include "Config.h"

InventoryInterface::InventoryInterface(
	const sf::Vector2f &centerPosition,
	const Inventory &inventory,
	const Equipment &equipment)
	:
	PanelInterface(
		centerPosition,
		"Inventory",
		2001),
	Listener({ EventType::UpdateInventoryInterface }),
	inventory_(inventory),
	equipment_(equipment),
	itemCardScroller_(
		sf::Vector2f(
			position_.x,
			position_.y + 6.0f),
		size_.x),
	closeButton_(
		sf::Vector2f(
			position_.x + size_.x * 0.25f,
			position_.y + size_.y - 8.0f),
		"Close",
		Config::Text::Size::medium)
{}

void InventoryInterface::onEvent(const Event &ev)
{
	itemCardScroller_.updateItemCards(
		inventory_,
		equipment_);
}

void InventoryInterface::update(float deltaTime)
{
	if (!isActive_)
	{
		return;
	}

	closeButton_.update(deltaTime);
}

void InventoryInterface::updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition)
{
	PanelInterface::updateOnMouseMove(mouseInterfacePosition);

	if (!isHovered_)
	{
		return;
	}

	closeButton_.updateOnMouseMove(mouseInterfacePosition);

	itemCardScroller_.updateOnMouseMove(mouseInterfacePosition);
}

void InventoryInterface::updateOnMouseWheelScroll(float delta)
{
	if (!isHovered_)
	{
		return;
	}

	itemCardScroller_.updateOnMouseWheelScroll(delta);
}

void InventoryInterface::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (!isActive_)
	{
		return;
	}

	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	closeButton_.updateOnMouseButtonPress(button);
}

void InventoryInterface::updateOnMouseButtonRelease(sf::Mouse::Button button)
{
	if (!isActive_)
	{
		return;
	}

	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	closeButton_.updateOnMouseButtonRelease(button);

	if (closeButton_.isHovered())
	{
		this->deactivate();
	}
	else
	{
		itemCardScroller_.updateOnMouseButtonPress(button); // TODO change this to updateOnMouseButtonRelease
	}
}

void InventoryInterface::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	if (!isActive_)
	{
		return;
	}

	panelSprite_.draw(target, states, scale);

	titleText_.draw(target, states, scale);

	itemCardScroller_.draw(target, states, scale);

	closeButton_.draw(target, states, scale);
}