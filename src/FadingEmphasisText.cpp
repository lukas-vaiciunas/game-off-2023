#include "FadingEmphasisText.h"

FadingEmphasisText::FadingEmphasisText(
	const sf::Vector2f &centerPosition,
	const sf::Vector2f &velocity,
	const sf::String &string,
	const sf::Color &fillColor,
	unsigned int characterSize,
	float durationSecs)
	:
	FadingText(
		centerPosition,
		velocity,
		string,
		fillColor,
		characterSize,
		durationSecs),
	state_(State::Expanding),
	scale_(1.0f),
	minScale_(1.0f),
	maxScale_(1.5f),
	velScale_(4.0f)
{}

void FadingEmphasisText::update(float deltaTime)
{
	FadingText::update(deltaTime);

	switch (state_)
	{
		case State::Expanding:
			scale_ += velScale_ * deltaTime;

			if (scale_ >= maxScale_)
			{
				scale_ = maxScale_;
				state_ = State::Contracting;
			}

			this->updateScale_();

			break;
		case State::Contracting:
			scale_ -= velScale_ * deltaTime;
			
			if (scale_ <= minScale_)
			{
				scale_ = minScale_;
				state_ = State::None;
			}

			this->updateScale_();

			break;
	}
}

void FadingEmphasisText::updateScale_()
{
	text_.setScale(
		sf::Vector2f(
			scale_,
			scale_));
}