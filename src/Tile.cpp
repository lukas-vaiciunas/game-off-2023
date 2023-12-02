#include "Tile.h"
#include "Constants.h"

Tile::Tile(
	const sf::Vector2u &coordinates,
	const sf::Texture &texture)
	:
	MapPositionable(coordinates),
	WorldDrawable(),
	sprite_(texture)
{
	const sf::Vector2f &spriteSize = sprite_.getSize();

	sf::Vector2f spritePosition(coordinate_.getPosition() * Constants::tileSize);

	if (spriteSize.x < Constants::tileSize)
	{
		spritePosition.x += (Constants::tileSize - spriteSize.x) * 0.5f;
	}
	else if (spriteSize.x > Constants::tileSize)
	{
		spritePosition.x -= (spriteSize.x - Constants::tileSize) * 0.5f;
	}
	
	if (spriteSize.y < Constants::tileSize)
	{
		spritePosition.y += (Constants::tileSize - spriteSize.y) * 0.5f;
	}
	else if (spriteSize.y > Constants::tileSize)
	{
		spritePosition.y -= (spriteSize.y - Constants::tileSize);
	}

	sprite_.setPosition(spritePosition);
}

void Tile::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	sprite_.draw(target, states, offset, scale);
}