#include "InterfaceText.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

InterfaceText::InterfaceText() :
	GameText(),
	InterfaceDrawable()
{}

void InterfaceText::setInterfacePosition(const sf::Vector2f &position)
{
	this->setPosition(position * Config::Interface::scale);
}

void InterfaceText::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	sf::RenderStates statesCopy(states);

	statesCopy.transform *= this->getTransform();

	target.draw(text_, statesCopy);
}