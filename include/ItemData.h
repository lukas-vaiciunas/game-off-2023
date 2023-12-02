#pragma once

class Item;

#include "ItemId.h"
#include <unordered_map>
#include <string>

class ItemData
{
public:
	ItemData(const ItemData &) = delete;
	ItemData(ItemData &&) = delete;

	ItemData &operator=(const ItemData &) = delete;
	ItemData &operator=(ItemData &&) = delete;

	static ItemData &getInstance();

	const Item *getItem(ItemId id) const;
private:
	ItemData();
	~ItemData();

	std::unordered_map<ItemId, Item *> items_;

	void load_(const std::string &filePath);
};