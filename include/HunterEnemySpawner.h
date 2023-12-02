#pragma once

class HunterEnemy;

#include "AlarmClock.h"
#include <cstdint>

class HunterEnemySpawner
{
public:
	HunterEnemySpawner();

	void update(float deltaTime);
private:
	AlarmClock hunterEnemySpawnClock_;

	uint8_t maxHunterEnemyDifficulty_;
	uint8_t hunterEnemyDifficulty_;

	HunterEnemy *generateHunterEnemy_();
};