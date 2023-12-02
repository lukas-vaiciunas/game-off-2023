#include "HunterEnemySpawner.h"
#include "HunterEnemy.h"
#include "Event.h"
#include "EventQueue.h"

HunterEnemySpawner::HunterEnemySpawner() :
	hunterEnemySpawnClock_(60),
	maxHunterEnemyDifficulty_(6),
	hunterEnemyDifficulty_(1)
{}

void HunterEnemySpawner::update(float deltaTime)
{
	hunterEnemySpawnClock_.update(deltaTime);

	if (hunterEnemySpawnClock_.isDone())
	{
		EventQueue &eventQueue = EventQueue::getInstance();

		hunterEnemySpawnClock_.resetSoft();

		eventQueue.send(
			new EventSpawnHunterEnemy(
				this->generateHunterEnemy_()));
		
		eventQueue.send(
			new EventOpenEyeball(
				"\"A hunter is coming!\""));

		if (hunterEnemyDifficulty_ < maxHunterEnemyDifficulty_)
		{
			++hunterEnemyDifficulty_;
		}
	}
}

HunterEnemy *HunterEnemySpawner::generateHunterEnemy_()
{
	TextureId helmetTextureId = 0;
	TextureId chestplateTextureId = 0;
	uint64_t health = 0;
	uint64_t damage = 0;

	switch (hunterEnemyDifficulty_)
	{
		case 1:
			helmetTextureId = 1101;
			chestplateTextureId = 1201;
			health = 4;
			damage = 3;
			break;
		case 2:
			helmetTextureId = 1102;
			chestplateTextureId = 1202;
			health = 8;
			damage = 6;
			break;
		case 3:
			helmetTextureId = 1103;
			chestplateTextureId = 1203;
			health = 16;
			damage = 12;
			break;
		case 4:
			helmetTextureId = 1104;
			chestplateTextureId = 1204;
			health = 32;
			damage = 20;
			break;
		case 5:
			helmetTextureId = 1105;
			chestplateTextureId = 1205;
			health = 64;
			damage = 36;
			break;
		case 6:
			helmetTextureId = 1106;
			chestplateTextureId = 1206;
			health = 128;
			damage = 72;
			break;
	}

	return new HunterEnemy(
		sf::Vector2u(0, 0), // TODO spawn out of player's vision
		40.0f,
		1,
		helmetTextureId,
		chestplateTextureId,
		health,
		damage,
		1.0f);
}