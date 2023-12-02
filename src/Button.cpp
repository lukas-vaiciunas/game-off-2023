#include "Button.h"
#include "Event.h"
#include "EventQueue.h"

Button::Button(
	const sf::Vector2f &position,
	const sf::Vector2f &size)
	:
	Hoverable(position, size),
	InterfaceDrawable(),
	state_(State::None),
	scale_(1.0f),
	minScale_(1.0f),
	maxScale_(1.25f),
	velScale_(2.0f)
{}

void Button::update(float deltaTime)
{
	switch (state_)
	{
		case State::Expand:
			scale_ += velScale_ * deltaTime;
			if (scale_ >= maxScale_)
			{
				scale_ = maxScale_;
			}
			this->applyScale_(scale_);
			break;
		case State::Contract:
			scale_ -= velScale_ * deltaTime;
			if (scale_ <= minScale_)
			{
				scale_ = minScale_;
			}
			this->applyScale_(scale_);
			break;
		case State::Return:
			scale_ -= velScale_ * deltaTime;
			if (scale_ <= minScale_)
			{
				scale_ = minScale_;
				state_ = State::None;
			}
			this->applyScale_(scale_);
			break;
	}
}

void Button::updateOnMouseMove(const sf::Vector2f &mouseRelativePosition)
{
	bool wasHovered = isHovered_;

	Hoverable::updateOnMouseMove(mouseRelativePosition);

	if (isHovered_ && !wasHovered)
	{
		state_ = State::Expand;

		EventQueue::getInstance().send(
			new EventPlaySound(
				1001));
	}
	else if (!isHovered_ && wasHovered)
	{
		state_ = State::Return;
	}
}

void Button::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left
		|| !isHovered_)
	{
		return;
	}

	state_ = State::Contract;

	EventQueue::getInstance().send(
		new EventPlaySound(
			1002));
}

void Button::updateOnMouseButtonRelease(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left
		|| !isHovered_)
	{
		return;
	}

	state_ = State::Expand;

	EventQueue::getInstance().send(
		new EventPlaySound(
			1003));
}