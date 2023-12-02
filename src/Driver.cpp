#include "Driver.h"
#include "MainMenuDriverState.h"
#include "PlayDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include <SFML/Graphics/RenderTarget.hpp>

Driver::Driver() :
	DriverInterface(),
	Listener({ EventType::ChangeDriverState, EventType::Quit }),
	eventQueue_(EventQueue::getInstance()),
	state_(nullptr),
	soundPool_(),
	isDone_(false)
{
	this->changeState_(DriverStateType::MainMenu);
}

Driver::~Driver()
{
	delete state_;
}

void Driver::onEvent(const Event &ev)
{
	switch (ev.getType())
	{
		case EventType::ChangeDriverState:
			this->changeState_(
				static_cast<const EventChangeDriverState &>(ev).getDriverStateType());
			break;
		case EventType::Quit:
			isDone_ = true;
			break;
	}
}

void Driver::update(float deltaTime)
{
	eventQueue_.dispatch();

	state_->update(deltaTime);

	soundPool_.update();
}

void Driver::updateOnMouseMove(int mouseX, int mouseY)
{
	state_->updateOnMouseMove(mouseX, mouseY);
}

void Driver::updateOnMouseWheelScroll(float delta)
{
	state_->updateOnMouseWheelScroll(delta);
}

void Driver::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	state_->updateOnMouseButtonPress(button);
}

void Driver::updateOnMouseButtonRelease(sf::Mouse::Button button)
{
	state_->updateOnMouseButtonRelease(button);
}

void Driver::updateOnKeyPress(sf::Keyboard::Key key)
{
	state_->updateOnKeyPress(key);
}

bool Driver::isDone() const
{
	return isDone_;
}

void Driver::draw(
	sf::RenderTarget &target,
	sf::RenderStates states) const
{
	target.draw(*state_, states);
}

void Driver::changeState_(DriverStateType stateType)
{
	delete state_;

	switch (stateType)
	{
		case DriverStateType::MainMenu:
			state_ = new MainMenuDriverState();
			break;
		case DriverStateType::Play:
			state_ = new PlayDriverState();
			break;
	}
}