#include "InterfaceSprite.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

InterfaceSprite::InterfaceSprite(const sf::Texture &texture) :
	InterfaceSprite(texture, sf::Vector2f(texture.getSize()))
{}

InterfaceSprite::InterfaceSprite(const sf::Texture &texture, const sf::Vector2f &size) :
	GameSprite(texture, size),
	InterfaceDrawable()
{}

void InterfaceSprite::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	sf::RenderStates statesCopy(states);

	statesCopy.transform.scale(scale);

	statesCopy.transform *= this->getTransform();

	statesCopy.texture = texture_;

	target.draw(vertices_, statesCopy);
}