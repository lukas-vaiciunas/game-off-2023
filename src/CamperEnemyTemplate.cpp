#include "CamperEnemyTemplate.h"
#include "CamperEnemy.h"
#include "Random.h"

CamperEnemyTemplate::CamperEnemyTemplate(
	TextureId animationTextureId,
	const std::vector<TextureId> &helmetTextureIds,
	const std::vector<TextureId> &chestplateTextureIds,
	uint64_t health,
	uint64_t damage,
	float speed,
	float attackRadius,
	float attackSecs)
	:
	animationTextureId_(animationTextureId),
	helmetTextureIds_(helmetTextureIds),
	chestplateTextureIds_(chestplateTextureIds),
	health_(health),
	damage_(damage),
	speed_(speed),
	attackRadius_(attackRadius),
	attackSecs_(attackSecs)
{}

CamperEnemy *CamperEnemyTemplate::create(
	const sf::Vector2u &coordinates,
	Partition<CamperEnemy, std::unordered_multimap<Coordinate, CamperEnemy *>> &partition) const
{
	std::mt19937 &engine = Random::getInstance().getEngine();

	std::uniform_int_distribution<size_t> helmetTextureIdsIndexDis(0, helmetTextureIds_.size() - 1);
	std::uniform_int_distribution<size_t> chestplateTextureIdsIndexDis(0, chestplateTextureIds_.size() - 1);

	return new CamperEnemy(
		partition,
		coordinates,
		speed_,
		animationTextureId_,
		helmetTextureIds_[helmetTextureIdsIndexDis(engine)],
		chestplateTextureIds_[chestplateTextureIdsIndexDis(engine)],
		health_,
		damage_,
		attackRadius_,
		attackSecs_);
}