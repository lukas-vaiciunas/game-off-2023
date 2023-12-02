#include "WorldText.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

WorldText::WorldText() :
	GameText(),
	WorldDrawable()
{}

void WorldText::setWorldPosition(const sf::Vector2f &position)
{
	const sf::Vector2f worldPosition = position * Config::World::scale;

	this->setPosition(worldPosition);
}

void WorldText::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	sf::RenderStates statesCopy(states);

	statesCopy.transform.translate(offset * Config::World::scale);
	
	statesCopy.transform *= this->getTransform();

	target.draw(text_, statesCopy);
}