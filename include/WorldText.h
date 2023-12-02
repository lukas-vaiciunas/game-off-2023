#pragma once

#include "GameText.h"
#include "WorldDrawable.h"

class WorldText :
	public GameText,
	public WorldDrawable
{
public:
	WorldText();

	void setWorldPosition(const sf::Vector2f &position);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
};