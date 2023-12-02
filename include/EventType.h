#pragma once

#include <cstdint>

enum class EventType : uint8_t
{
	ChangeDriverState,
	Quit,
	PlaySound,
	OpenEyeball,
	CloseEyeball,
	CamperEnemyDeath,
	HealPlayer,
	HurtPlayer,
	AddItem,
	RemoveItem,
	EquipItem,
	DequipItem,
	ChangePlayerWeapon,
	ChangePlayerHelmet,
	ChangePlayerChestplate,
	ChangePlayerAxe,
	ChangePlayerPickaxe,
	Harvest,
	MovePlayerAndHarvest,
	Attack,
	MovePlayerAndAttack,
	MovePlayer,
	StopPlayer,
	SpawnHunterEnemy,
	SpawnFloatingText,
	SpawnPlayerFloatingText,
	SpawnFloatingIconText,
	SpawnFloatingEmphasisText,
	SpawnDeathParticles,
	UpdateInventoryInterface,
	UpdateCraftingInterface,
	UpdateHealthInterface,
	ViewCraftingList,
	ViewCraftingItem
};