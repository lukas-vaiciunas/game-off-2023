#pragma once

#include "GameSprite.h"
#include "WorldDrawable.h"

class WorldSprite :
	public GameSprite,
	public WorldDrawable
{
public:
	WorldSprite();
	WorldSprite(const sf::Texture &texture);
	WorldSprite(const sf::Texture &texture, const sf::Vector2f &size);

	virtual ~WorldSprite() = default;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
private:
	WorldSprite(const sf::Texture *texture, const sf::Vector2f &size);
};