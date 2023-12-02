#pragma once

#include "Fading.h"
#include "WorldSprite.h"

class Particle :
	public Fading,
	public WorldDrawable
{
public:
	Particle(
		const sf::Vector2f &position,
		const sf::Vector2f &velocity,
		const sf::Texture &texture,
		float durationSecs);

	virtual ~Particle() = default;

	virtual void update(float deltaTime) override;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
protected:
	WorldSprite sprite_;

	sf::Vector2f position_;
	sf::Vector2f velocity_;

	void updatePosition_(float deltaTime);
	void applyAlpha_(uint8_t alpha) override;
};