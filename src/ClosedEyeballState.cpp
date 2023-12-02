#include "ClosedEyeballState.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"

ClosedEyeballState::ClosedEyeballState(const sf::Vector2f &position) :
	EyeballState(),
	spriteButton_(
		sf::Vector2f(0.0f, 0.0f),
		TextureData::getInstance().getTexture(901))
{
	spriteButton_.setPosition(position);
}

void ClosedEyeballState::update(float deltaTime)
{
	spriteButton_.update(deltaTime);
}

void ClosedEyeballState::updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition)
{
	spriteButton_.updateOnMouseMove(mouseInterfacePosition);
}

void ClosedEyeballState::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	spriteButton_.updateOnMouseButtonPress(button);
}

void ClosedEyeballState::updateOnMouseButtonRelease(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	spriteButton_.updateOnMouseButtonRelease(button);

	if (spriteButton_.isHovered())
	{
		EventQueue::getInstance().send(
			new EventOpenEyeball(
				"\"Please don't poke me.\""));
	}
}

bool ClosedEyeballState::isHovered() const
{
	return spriteButton_.isHovered();
}

void ClosedEyeballState::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	spriteButton_.draw(target, states, scale);
}