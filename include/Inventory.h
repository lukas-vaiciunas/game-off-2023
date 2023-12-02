#pragma once

class Equipment;

#include "Listener.h"
#include "ItemId.h"
#include <map>

class Inventory : public Listener
{
public:
	Inventory(const Equipment &equipment);

	void onEvent(const Event &ev) override;

	bool contains(ItemId itemId, uint64_t amount) const;

	const std::map<ItemId, uint64_t> &getItems() const;
private:
	const Equipment &equipment_;

	std::map<ItemId, uint64_t> items_;

	void addItem_(ItemId itemId, uint64_t amount);
	void removeItem_(ItemId itemId, uint64_t amount);

	void sendUpdates_() const;
};