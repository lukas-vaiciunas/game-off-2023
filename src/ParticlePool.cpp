#include "ParticlePool.h"
#include "GravityParticle.h"
#include "Event.h"
#include "TextureData.h"
#include "Random.h"

ParticlePool::ParticlePool(Size capacity) :
	Pool(capacity),
	Listener({ EventType::SpawnDeathParticles }),
	WorldDrawable()
{}

void ParticlePool::onEvent(const Event &ev)
{
	const EventSpawnDeathParticles &castEv = static_cast<const EventSpawnDeathParticles &>(ev);

	this->spawnDeathParticles_(
		castEv.getPosition(),
		castEv.getFloorY());
}

void ParticlePool::update(float deltaTime)
{
	for (Size i = 0; i < numLive_; )
	{
		objects_[i]->update(deltaTime);

		if (!objects_[i]->isLive())
		{
			this->remove_(i);
		}
		else ++i;
	}
}

void ParticlePool::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	for (Size i = 0; i < numLive_; ++i)
	{
		objects_[i]->draw(target, states, offset, scale);
	}
}

void ParticlePool::spawnDeathParticles_(
	const sf::Vector2f &position,
	float floorY)
{
	const TextureData &textureData = TextureData::getInstance();

	std::mt19937 &engine = Random::getInstance().getEngine();

	std::uniform_real_distribution<float> xVelocityDis(-12.0f, 12.0f);
	std::uniform_real_distribution<float> yVelocityDis(-56.0f, -24.0f);

	for (uint8_t i = 0; i < 4; ++i)
	{
		if (this->isFull_())
		{
			break;
		}

		this->add_(
			new GravityParticle(
				position,
				sf::Vector2f(
					xVelocityDis(engine),
					yVelocityDis(engine)),
				128.0f,
				floorY,
				2,
				textureData.getTexture(3001),
				2.0f));
	}
}