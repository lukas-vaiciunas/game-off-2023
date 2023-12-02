#pragma once

namespace sf
{
	template<typename> class Vector2;
	typedef Vector2<unsigned int> Vector2u;
}

class CamperEnemy;
class Coordinate;
template<typename, typename> class Partition;

#include "TextureId.h"
#include <unordered_map>

class CamperEnemyTemplate
{
public:
	CamperEnemyTemplate(
		TextureId animationTextureId,
		const std::vector<TextureId> &helmetTextureIds,
		const std::vector<TextureId> &chestplateTextureIds,
		uint64_t health,
		uint64_t damage,
		float speed,
		float attackRadius,
		float attackSecs);

	CamperEnemy *create(
		const sf::Vector2u &coordinates,
		Partition<CamperEnemy, std::unordered_multimap<Coordinate, CamperEnemy *>> &partition) const;
private:
	TextureId animationTextureId_;
	std::vector<TextureId> helmetTextureIds_;
	std::vector<TextureId> chestplateTextureIds_;
	uint64_t health_;
	uint64_t damage_;
	float speed_;
	float attackRadius_;
	float attackSecs_;
};