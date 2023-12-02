#include "ItemCard.h"
#include "Item.h"
#include "ItemData.h"
#include "TextureData.h"
#include "Config.h"

ItemCard::ItemCard(ItemId itemId, uint64_t amount, const sf::Vector2f &size) :
	Hoverable(
		sf::Vector2f(0.0f, 0.0f),
		size),
	InterfaceDrawable(),
	itemId_(itemId),
	sprite_(
		TextureData::getInstance().getTexture(
			ItemData::getInstance().getItem(
				itemId)->getTextureId())),
	equippedIconSprite_(
		TextureData::getInstance().getTexture(
			2111)),
	nameText_(),
	amountText_(),
	isEquipped_(false)
{
	sprite_.setOrigin(sprite_.getSize() * 0.5f);

	equippedIconSprite_.setOrigin(equippedIconSprite_.getSize() * 0.5f);

	const Item *item = ItemData::getInstance().getItem(itemId);

	nameText_.setString(item->getName());
	nameText_.setCharacterSize(Config::Text::Size::medium);
	nameText_.setFillColor(item->getRarityColor());
	nameText_.setOutlineColor(sf::Color(0, 0, 0));

	const sf::FloatRect nameTextLocalBounds = nameText_.getLocalBounds();
	nameText_.setOrigin(
		nameTextLocalBounds.left,
		nameTextLocalBounds.top + nameTextLocalBounds.height * 0.5f);

	amountText_.setString("x" + std::to_string(amount));
	amountText_.setCharacterSize(Config::Text::Size::medium);
	amountText_.setFillColor(sf::Color(225, 225, 225));
	amountText_.setOutlineColor(sf::Color(0, 0, 0));

	const sf::FloatRect amountTextLocalBounds = amountText_.getLocalBounds();
	amountText_.setOrigin(
		amountTextLocalBounds.left,
		amountTextLocalBounds.top + amountTextLocalBounds.height * 0.5f);
}

void ItemCard::setEquipped(bool isEquipped)
{
	isEquipped_ = isEquipped;
}

void ItemCard::setPosition(const sf::Vector2f &position)
{
	if (position_ == position)
	{
		return;
	}

	position_ = position;

	const float centerY = position_.y + size_.y * 0.5f;

	sprite_.setPosition(
		sf::Vector2f(
			position_.x + 8.0f,
			centerY));

	nameText_.setInterfacePosition(
		sf::Vector2f(
			position_.x + 16.0f,
			centerY));

	equippedIconSprite_.setPosition(
		sf::Vector2f(
			position_.x + 46.0f,
			centerY));

	amountText_.setInterfacePosition(
		sf::Vector2f(
			position_.x + 52.0f,
			centerY));
}

ItemId ItemCard::getItemId() const
{
	return itemId_;
}

void ItemCard::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	sprite_.draw(target, states, scale);

	if (isEquipped_)
	{
		equippedIconSprite_.draw(target, states, scale);
	}
	
	nameText_.draw(target, states, scale);
	amountText_.draw(target, states, scale);
}