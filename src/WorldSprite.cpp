#include "WorldSprite.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

WorldSprite::WorldSprite() :
	WorldSprite(nullptr, sf::Vector2f(0.0f, 0.0f))
{}

WorldSprite::WorldSprite(const sf::Texture &texture) :
	WorldSprite(&texture, sf::Vector2f(texture.getSize()))
{}

WorldSprite::WorldSprite(const sf::Texture &texture, const sf::Vector2f &size) :
	WorldSprite(&texture, size)
{}

WorldSprite::WorldSprite(const sf::Texture *texture, const sf::Vector2f &size) :
	GameSprite(texture, size),
	WorldDrawable()
{}

void WorldSprite::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	sf::RenderStates statesCopy(states);

	statesCopy.transform.scale(scale);
	statesCopy.transform.translate(offset);

	statesCopy.transform *= this->getTransform();

	statesCopy.texture = texture_;

	target.draw(vertices_, statesCopy);
}