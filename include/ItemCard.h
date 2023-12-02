#pragma once

#include "Hoverable.h"
#include "InterfaceSprite.h"
#include "InterfaceText.h"
#include "ItemId.h"

class ItemCard :
	public Hoverable,
	public InterfaceDrawable
{
public:
	ItemCard(ItemId itemId, uint64_t amount, const sf::Vector2f &size);

	void setEquipped(bool isEquipped);

	void setPosition(const sf::Vector2f &position);

	ItemId getItemId() const;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	ItemId itemId_;

	InterfaceSprite sprite_;
	InterfaceSprite equippedIconSprite_;
	InterfaceText nameText_;
	InterfaceText amountText_;

	bool isEquipped_;
};