#pragma once

#include "MapPositionable.h"
#include "WorldSprite.h"

class Tile :
	public MapPositionable,
	public WorldDrawable
{
public:
	Tile(
		const sf::Vector2u &coordinates,
		const sf::Texture &texture);

	virtual ~Tile() = default;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
protected:
	WorldSprite sprite_;

};