#pragma once

#include "Listener.h"
#include "ItemId.h"

class Equipment : public Listener
{
public:
	Equipment();

	void onEvent(const Event &ev) override;

	std::unordered_set<ItemId> getEquippedItemIds() const;
private:
	ItemId weaponId_;
	ItemId helmetId_;
	ItemId chestplateId_;
	ItemId axeId_;
	ItemId pickaxeId_;

	void equipItem_(ItemId itemId);
	void equipWeapon_(ItemId itemId);
	void equipHelmet_(ItemId itemId);
	void equipChestplate_(ItemId itemId);
	void equipAxe_(ItemId itemId);
	void equipPickaxe_(ItemId itemId);

	void dequipItem_(ItemId itemId);

	void sendUpdates_() const;
};