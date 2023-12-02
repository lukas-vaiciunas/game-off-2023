#include "Interface.h"

Interface::Interface(
	const sf::Vector2f &position,
	const sf::Vector2f &size)
	:
	Hoverable(position, size),
	InterfaceDrawable(),
	isActive_(false)
{}

void Interface::updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition)
{
	if (!isActive_)
	{
		return;
	}

	Hoverable::updateOnMouseMove(mouseInterfacePosition);
}

void Interface::toggle()
{
	if (isActive_)
	{
		this->deactivate();
	}
	else
	{
		this->activate();
	}
}

void Interface::activate()
{
	isActive_ = true;
}

void Interface::deactivate()
{
	isActive_ = false;
	isHovered_ = false;
}