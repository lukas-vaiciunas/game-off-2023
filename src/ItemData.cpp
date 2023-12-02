#include "ItemData.h"
#include "ResourceItem.h"
#include "FoodItem.h"
#include "WeaponItem.h"
#include "HelmetItem.h"
#include "ChestplateItem.h"
#include "AxeItem.h"
#include "PickaxeItem.h"
#include <fstream>
#include <sstream>
#include <algorithm>

ItemData::ItemData() :
	items_()
{
	this->load_("./data/items.txt");
}

ItemData::~ItemData()
{
	for (auto it = items_.begin(); it != items_.end(); ++it)
	{
		delete it->second;
	}
}

ItemData &ItemData::getInstance()
{
	static ItemData instance;
	return instance;
}

const Item *ItemData::getItem(ItemId id) const
{
	return items_.at(id);
}

void ItemData::load_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		fprintf(stderr, "Failed to open \"%s\" in ItemData::load_\n", filePath.c_str());
		return;
	}

	std::string line;
	std::stringstream ss;

	ItemId itemId;
	std::string itemNameString;
	TextureId itemTextureId;
	uint64_t itemRarity;
	std::string itemTypeString;

	while (std::getline(in, line))
	{
		ss.clear();
		ss.str(line);

		ss >> itemId >> itemNameString >> itemTextureId >> itemRarity >> itemTypeString;

		std::replace(itemNameString.begin(), itemNameString.end(), '_', ' ');

		if (itemTypeString == "RESOURCE")
		{
			items_.emplace(itemId, new ResourceItem(itemNameString, static_cast<uint8_t>(itemRarity), itemTextureId));
		}
		else if (itemTypeString == "FOOD")
		{
			uint64_t nutrition;
			ss >> nutrition;

			items_.emplace(itemId, new FoodItem(itemNameString, static_cast<uint8_t>(itemRarity), itemTextureId, nutrition));
		}
		else if (itemTypeString == "WEAPON")
		{
			uint64_t damage;
			ss >> damage;

			items_.emplace(itemId, new WeaponItem(itemNameString, static_cast<uint8_t>(itemRarity), itemTextureId, damage));
		}
		else if (itemTypeString == "HELMET")
		{
			uint64_t armor;
			ss >> armor;

			items_.emplace(itemId, new HelmetItem(itemNameString, static_cast<uint8_t>(itemRarity), itemTextureId, armor));
		}
		else if (itemTypeString == "CHESTPLATE")
		{
			uint64_t armor;
			ss >> armor;

			items_.emplace(itemId, new ChestplateItem(itemNameString, static_cast<uint8_t>(itemRarity), itemTextureId, armor));
		}
		else if (itemTypeString == "AXE")
		{
			uint64_t power;
			ss >> power;

			items_.emplace(itemId, new AxeItem(itemNameString, static_cast<uint8_t>(itemRarity), itemTextureId, static_cast<uint8_t>(power)));
		}
		else if (itemTypeString == "PICKAXE")
		{
			uint64_t power;
			ss >> power;

			items_.emplace(itemId, new PickaxeItem(itemNameString, static_cast<uint8_t>(itemRarity), itemTextureId, static_cast<uint8_t>(power)));
		}
	}

	in.close();
}