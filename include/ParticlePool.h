#pragma once

#include "Pool.h"
#include "Particle.h"
#include "Listener.h"

class ParticlePool :
	public Pool<Particle>,
	public Listener,
	public WorldDrawable
{
public:
	ParticlePool(Size capacity);

	void onEvent(const Event &ev) override;

	void update(float deltaTime);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
private:
	void spawnDeathParticles_(
		const sf::Vector2f &position,
		float floorY);
};