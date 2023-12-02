#include "ItemRecipeCard.h"
#include "ItemRecipe.h"
#include "Item.h"
#include "ItemData.h"
#include "TextureData.h"
#include "Config.h"

ItemRecipeCard::ItemRecipeCard(
	const ItemRecipe &itemRecipe,
	const sf::Vector2f &size)
	:
	Hoverable(
		sf::Vector2f(0.0f, 0.0f),
		size),
	InterfaceDrawable(),
	productSprite_(
		TextureData::getInstance().getTexture(
			ItemData::getInstance().getItem(
				itemRecipe.getProductItemId())->getTextureId())),
	statusSprite_(TextureData::getInstance().getTexture(2101)),
	productNameText_(),
	isCraftable_(false)
{
	productSprite_.setOrigin(productSprite_.getSize() * 0.5f);

	const Item *product = ItemData::getInstance().getItem(itemRecipe.getProductItemId());

	productNameText_.setString(product->getName());
	productNameText_.setCharacterSize(Config::Text::Size::medium);
	productNameText_.setFillColor(product->getRarityColor());
	productNameText_.setOutlineColor(sf::Color(0, 0, 0));

	const sf::FloatRect productNameTextLocalBounds = productNameText_.getLocalBounds();
	productNameText_.setOrigin(
		productNameTextLocalBounds.left,
		productNameTextLocalBounds.top + productNameTextLocalBounds.height * 0.5f);

	this->updateStatusSpriteOrigin_();
}

void ItemRecipeCard::setPosition(const sf::Vector2f &position)
{
	if (position_ == position)
	{
		return;
	}

	position_ = position;

	const float centerY = position_.y + size_.y * 0.5f;

	productSprite_.setPosition(
		sf::Vector2f(
			position_.x + 8.0f,
			centerY));

	productNameText_.setInterfacePosition(
		sf::Vector2f(
			position_.x + 16.0f,
			centerY));

	statusSprite_.setPosition(
		sf::Vector2f(
			position_.x + 56.0f,
			centerY));
}

void ItemRecipeCard::setStatus(bool isCraftable)
{
	if (isCraftable_ == isCraftable)
	{
		return;
	}

	isCraftable_ = isCraftable;

	statusSprite_.setTexture(
		TextureData::getInstance().getTexture(
			isCraftable_ ? 2102 : 2101));

	this->updateStatusSpriteOrigin_();
}

void ItemRecipeCard::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	productSprite_.draw(target, states, scale);
	productNameText_.draw(target, states, scale);
	statusSprite_.draw(target, states, scale);
}

void ItemRecipeCard::updateStatusSpriteOrigin_()
{
	statusSprite_.setOrigin(statusSprite_.getSize() * 0.5f);
}