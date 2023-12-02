#include "ListCraftingInterfaceState.h"
#include "CraftingInterface.h"
#include "Config.h"

ListCraftingInterfaceState::ListCraftingInterfaceState(CraftingInterface &parent) :
	CraftingInterfaceState(parent),
	itemRecipeCardScroller_(
		sf::Vector2f(
			parent.position_.x,
			parent_.position_.y + 6.0f),
		parent_.size_.x,
		parent_.crafting_,
		parent_.inventory_),
	closeButton_(
		sf::Vector2f(
			parent.position_.x + parent.size_.x * 0.25f,
			parent_.position_.y + parent_.size_.y - 8.0f),
		"Close",
		Config::Text::Size::medium)
{}

void ListCraftingInterfaceState::updateOnEvent()
{
	itemRecipeCardScroller_.updateItemRecipeCards(parent_.crafting_, parent_.inventory_);
}

void ListCraftingInterfaceState::update(float deltaTime)
{
	closeButton_.update(deltaTime);
}

void ListCraftingInterfaceState::updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition)
{
	closeButton_.updateOnMouseMove(mouseInterfacePosition);

	itemRecipeCardScroller_.updateOnMouseMove(mouseInterfacePosition);
}

void ListCraftingInterfaceState::updateOnMouseWheelScroll(float delta)
{
	itemRecipeCardScroller_.updateOnMouseWheelScroll(delta);
}

void ListCraftingInterfaceState::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	closeButton_.updateOnMouseButtonPress(button);
}

void ListCraftingInterfaceState::updateOnMouseButtonRelease(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	closeButton_.updateOnMouseButtonRelease(button);

	if (closeButton_.isHovered())
	{
		parent_.deactivate();
	}
	else
	{
		itemRecipeCardScroller_.updateOnMouseButtonPress(button); // TODO change to updateOnMouseButtonRelease
	}
}

void ListCraftingInterfaceState::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	itemRecipeCardScroller_.draw(target, states, scale);

	closeButton_.draw(target, states, scale);
}