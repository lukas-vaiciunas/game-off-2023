#include "ItemRecipeCardScroller.h"
#include "Crafting.h"
#include "Inventory.h"
#include "Event.h"
#include "EventQueue.h"

ItemRecipeCardScroller::ItemRecipeCardScroller(
	const sf::Vector2f &position,
	float width,
	const Crafting &crafting,
	const Inventory &inventory)
	:
	Scrollable(6),
	InterfaceDrawable(),
	itemRecipeCards_(),
	position_(position),
	width_(width)
{
	this->initializeItemRecipeCards_(crafting, inventory);
}

void ItemRecipeCardScroller::updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition)
{
	for (uint64_t i = 0; i < numObjectsDisplayed_; ++i)
	{
		itemRecipeCards_[scrollIndex_ + i].updateOnMouseMove(mouseInterfacePosition);
	}
}

void ItemRecipeCardScroller::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	for (uint64_t i = 0; i < numObjectsDisplayed_; ++i)
	{
		if (itemRecipeCards_[scrollIndex_ + i].isHovered())
		{
			EventQueue::getInstance().send(
				new EventViewCraftingItem(
					scrollIndex_ + i));
			break;
		}
	}
}

void ItemRecipeCardScroller::updateItemRecipeCards(
	const Crafting &crafting,
	const Inventory &inventory)
{
	const std::vector<ItemRecipe> &itemRecipes = crafting.getItemRecipes();

	for (size_t i = 0; i < itemRecipes.size(); ++i)
	{
		const std::vector<std::pair<ItemId, uint64_t>> &ingredients = itemRecipes[i].getIngredients();

		bool isCraftable = true;

		for (auto it = ingredients.begin(); it != ingredients.end(); ++it)
		{
			if (!inventory.contains(it->first, it->second))
			{
				isCraftable = false;
				break;
			}
		}

		itemRecipeCards_[i].setStatus(isCraftable);
	}
}

void ItemRecipeCardScroller::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	for (uint64_t i = 0; i < numObjectsDisplayed_; ++i)
	{
		itemRecipeCards_[scrollIndex_ + i].draw(target, states, scale);
	}
}

void ItemRecipeCardScroller::initializeItemRecipeCards_(
	const Crafting &crafting,
	const Inventory &inventory)
{
	const std::vector<ItemRecipe> &itemRecipes = crafting.getItemRecipes();
	const sf::Vector2f cardSize(width_, 8.0f);

	itemRecipeCards_.clear();

	for (size_t i = 0; i < itemRecipes.size(); ++i)
	{
		ItemRecipeCard itemRecipeCard(
			itemRecipes[i],
			cardSize);

		itemRecipeCards_.emplace_back(std::move(itemRecipeCard));
	}

	this->setNumObjects_(itemRecipeCards_.size());
	this->updateObjectPositions_();
	this->updateItemRecipeCards(crafting, inventory);
}

void ItemRecipeCardScroller::updateObjectPositions_()
{
	for (uint64_t i = 0; i < numObjectsDisplayed_; ++i)
	{
		itemRecipeCards_[scrollIndex_ + i].setPosition(
			sf::Vector2f(
				position_.x,
				position_.y + 10.0f * i));
	}
}