#include "ItemCraftingInterfaceState.h"
#include "CraftingInterface.h"
#include "Crafting.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemData.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"
#include "Config.h"

ItemCraftingInterfaceState::ItemCraftingInterfaceState(
	CraftingInterface &parent,
	size_t itemRecipeIndex)
	:
	CraftingInterfaceState(parent),
	itemRecipeIndex_(itemRecipeIndex),
	itemRecipeCard_(
		parent.crafting_.getItemRecipes()[itemRecipeIndex],
		sf::Vector2f(parent.size_.x, 8.0f)),
	requirementsText_(),
	ingredientSprites_(),
	ingredientAmountTexts_(),
	ingredientStatusSprites_(),
	numIngredients_(0),
	backButton_(
		sf::Vector2f(
			parent_.position_.x + parent_.size_.x * 0.25f,
			parent_.position_.y + parent_.size_.y - 8.0f),
		"Back",
		Config::Text::Size::medium),
	craftButton_(
		sf::Vector2f(
			parent_.position_.x + parent_.size_.x * 0.75f,
			parent_.position_.y + parent_.size_.y - 8.0f),
		"Craft",
		Config::Text::Size::medium),
	isCraftable_(false)
{
	const TextureData &textureData = TextureData::getInstance();
	const ItemData &itemData = ItemData::getInstance();
	const std::vector<std::pair<ItemId, uint64_t>> &ingredients = parent_.crafting_.getItemRecipes()[itemRecipeIndex_].getIngredients();

	numIngredients_ = ingredients.size();

	itemRecipeCard_.setPosition(
		sf::Vector2f(
			parent_.position_.x,
			parent_.position_.y + 6.0f));

	requirementsText_.setString("Requirements");
	requirementsText_.setCharacterSize(Config::Text::Size::medium);
	requirementsText_.setFillColor(sf::Color(225, 225, 225));
	requirementsText_.setOutlineColor(sf::Color(0, 0, 0));

	const sf::FloatRect requirementsTextLocalBounds = requirementsText_.getLocalBounds();

	requirementsText_.setOrigin(
		sf::Vector2f(
			requirementsTextLocalBounds.left + requirementsTextLocalBounds.width * 0.5f,
			requirementsTextLocalBounds.top + requirementsTextLocalBounds.height * 0.5f));

	requirementsText_.setInterfacePosition(
		sf::Vector2f(
			parent_.position_.x + parent_.size_.x * 0.5f,
			parent_.position_.y + 24.0f));

	for (size_t i = 0; i < ingredients.size(); ++i)
	{
		const float centerY = parent_.position_.y + 32.0f + 10.0f * i;

		InterfaceSprite ingredientSprite(
			textureData.getTexture(
				itemData.getItem(
					ingredients[i].first)->getTextureId()));

		ingredientSprite.setOrigin(ingredientSprite.getSize() * 0.5f);

		ingredientSprite.setPosition(
			sf::Vector2f(
				parent_.position_.x + 8.0f,
				centerY));

		ingredientSprites_.emplace_back(std::move(ingredientSprite));

		InterfaceText ingredientAmountText;

		ingredientAmountText.setString("x" + std::to_string(ingredients[i].second));
		ingredientAmountText.setCharacterSize(Config::Text::Size::medium);
		ingredientAmountText.setFillColor(sf::Color(225, 225, 225));
		ingredientAmountText.setOutlineColor(sf::Color(0, 0, 0));

		const sf::FloatRect ingredientAmountTextLocalBounds = ingredientAmountText.getLocalBounds();
		ingredientAmountText.setOrigin(
			sf::Vector2f(
				ingredientAmountTextLocalBounds.left + ingredientAmountTextLocalBounds.width * 0.5f,
				ingredientAmountTextLocalBounds.top + ingredientAmountTextLocalBounds.height * 0.5f));

		ingredientAmountText.setInterfacePosition(
			sf::Vector2f(
				parent_.position_.x + 16.0f,
				centerY));

		ingredientAmountTexts_.emplace_back(std::move(ingredientAmountText));

		InterfaceSprite ingredientStatusSprite(textureData.getTexture(1101));

		ingredientStatusSprite.setOrigin(ingredientStatusSprite.getSize() * 0.5f);
		ingredientStatusSprite.setPosition(
			sf::Vector2f(
				parent_.position_.x + 56.0f,
				centerY));

		ingredientStatusSprites_.emplace_back(std::move(ingredientStatusSprite));
	}

	this->updateStatus_();
}

void ItemCraftingInterfaceState::updateOnEvent()
{
	this->updateStatus_();
}

void ItemCraftingInterfaceState::update(float deltaTime)
{
	backButton_.update(deltaTime);
	craftButton_.update(deltaTime);
}

void ItemCraftingInterfaceState::updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition)
{
	backButton_.updateOnMouseMove(mouseInterfacePosition);
	craftButton_.updateOnMouseMove(mouseInterfacePosition);
}

void ItemCraftingInterfaceState::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	backButton_.updateOnMouseButtonPress(button);
	craftButton_.updateOnMouseButtonPress(button);
}

void ItemCraftingInterfaceState::updateOnMouseButtonRelease(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	backButton_.updateOnMouseButtonRelease(button);
	craftButton_.updateOnMouseButtonRelease(button);

	if (backButton_.isHovered())
	{
		EventQueue::getInstance().send(
			new EventViewCraftingList());
	}
	else if (isCraftable_ && craftButton_.isHovered())
	{
		// TODO optimize this by having a batch remove + add event
		const std::vector<std::pair<ItemId, uint64_t>> &ingredients = parent_.crafting_.getItemRecipes()[itemRecipeIndex_].getIngredients();
		EventQueue &eventQueue = EventQueue::getInstance();

		for (auto it = ingredients.begin(); it != ingredients.end(); ++it)
		{
			eventQueue.send(
				new EventRemoveItem(
					it->first,
					it->second));
		}

		eventQueue.send(
			new EventAddItem(
				parent_.crafting_.getItemRecipes()[itemRecipeIndex_].getProductItemId(),
				1));

		eventQueue.send(
			new EventPlaySound(
				302));
	}
}

void ItemCraftingInterfaceState::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	itemRecipeCard_.draw(target, states, scale);

	requirementsText_.draw(target, states, scale);

	for (uint64_t i = 0; i < numIngredients_; ++i)
	{
		ingredientSprites_[i].draw(target, states, scale);
		ingredientAmountTexts_[i].draw(target, states, scale);
		ingredientStatusSprites_[i].draw(target, states, scale);
	}

	backButton_.draw(target, states, scale);
	craftButton_.draw(target, states, scale);
}

void ItemCraftingInterfaceState::updateStatus_()
{
	const TextureData &textureData = TextureData::getInstance();
	const std::vector<std::pair<ItemId, uint64_t>> &ingredients = parent_.crafting_.getItemRecipes()[itemRecipeIndex_].getIngredients();

	isCraftable_ = true;

	for (size_t i = 0; i < ingredients.size(); ++i)
	{
		// TODO optimize this by creating a class for each ingredient that holds state (whether it is craftable)
		if (parent_.inventory_.contains(
			ingredients[i].first,
			ingredients[i].second))
		{
			ingredientStatusSprites_[i].setTexture(textureData.getTexture(2102));
		}
		else
		{
			ingredientStatusSprites_[i].setTexture(textureData.getTexture(2101));
			isCraftable_ = false;
		}

		ingredientSprites_[i].setOrigin(ingredientSprites_[i].getSize() * 0.5f);
	}

	itemRecipeCard_.setStatus(isCraftable_);

	craftButton_.setFillColor(
		(isCraftable_
			? sf::Color(252, 224, 140)
			: sf::Color(176, 176, 176)));
}