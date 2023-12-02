#include "CraftingInterface.h"
#include "ListCraftingInterfaceState.h"
#include "ItemCraftingInterfaceState.h"
#include "Event.h"

CraftingInterface::CraftingInterface(
	const sf::Vector2f &centerPosition,
	const Crafting &crafting,
	const Inventory &inventory)
	:
	PanelInterface(
		centerPosition,
		"Crafting",
		2001),
	Listener(
		{
			EventType::UpdateCraftingInterface,
			EventType::ViewCraftingList,
			EventType::ViewCraftingItem
		}),
	crafting_(crafting),
	inventory_(inventory),
	state_(new ListCraftingInterfaceState(*this))
{}

CraftingInterface::~CraftingInterface()
{
	delete state_;
}

void CraftingInterface::onEvent(const Event &ev)
{
	switch (ev.getType())
	{
		case EventType::UpdateCraftingInterface:
			state_->updateOnEvent();
			break;
		case EventType::ViewCraftingList:
			delete state_;
			state_ = new ListCraftingInterfaceState(*this);
			break;
		case EventType::ViewCraftingItem:
			delete state_;
			state_ = new ItemCraftingInterfaceState(
				*this,
				static_cast<const EventViewCraftingItem &>(ev).getItemRecipeIndex());
			break;
	}
}

void CraftingInterface::update(float deltaTime)
{
	if (!isActive_)
	{
		return;
	}

	state_->update(deltaTime);
}

void CraftingInterface::updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition)
{
	PanelInterface::updateOnMouseMove(mouseInterfacePosition);

	if (!isHovered_)
	{
		return;
	}

	state_->updateOnMouseMove(mouseInterfacePosition);
}

void CraftingInterface::updateOnMouseWheelScroll(float delta)
{
	if (!isHovered_)
	{
		return;
	}

	state_->updateOnMouseWheelScroll(delta);
}

void CraftingInterface::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (!isActive_)
	{
		return;
	}

	state_->updateOnMouseButtonPress(button);
}

void CraftingInterface::updateOnMouseButtonRelease(sf::Mouse::Button button)
{
	if (!isActive_)
	{
		return;
	}

	state_->updateOnMouseButtonRelease(button);
}

void CraftingInterface::draw(
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

	state_->draw(target, states, scale);
}