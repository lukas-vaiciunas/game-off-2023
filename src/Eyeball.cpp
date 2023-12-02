#include "Eyeball.h"
#include "OpenedEyeballState.h"
#include "ClosedEyeballState.h"
#include "Event.h"

Eyeball::Eyeball(const sf::Vector2f &position) :
	Listener(
		{
			EventType::OpenEyeball,
			EventType::CloseEyeball
		}),
	InterfaceDrawable(),
	state_(new ClosedEyeballState(position)),
	position_(position)
{}

Eyeball::~Eyeball()
{
	delete state_;
}

void Eyeball::onEvent(const Event &ev)
{
	switch (ev.getType())
	{
		case EventType::OpenEyeball:
			delete state_;
			state_ = new OpenedEyeballState(
				position_,
				static_cast<const EventOpenEyeball &>(ev).getTextString());
			break;
		case EventType::CloseEyeball:
			delete state_;
			state_ = new ClosedEyeballState(position_);
			break;
	}
}

void Eyeball::update(float deltaTime)
{
	state_->update(deltaTime);
}

void Eyeball::updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition)
{
	state_->updateOnMouseMove(mouseInterfacePosition);
}

void Eyeball::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	state_->updateOnMouseButtonPress(button);
}

void Eyeball::updateOnMouseButtonRelease(sf::Mouse::Button button)
{
	state_->updateOnMouseButtonRelease(button);
}

bool Eyeball::isHovered() const
{
	return state_->isHovered();
}

void Eyeball::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	state_->draw(target, states, scale);
}