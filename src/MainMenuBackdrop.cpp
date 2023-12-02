#include "MainMenuBackdrop.h"
#include "TextureData.h"
#include "Config.h"

MainMenuBackdrop::MainMenuBackdrop() :
	InterfaceDrawable(),
	backdropSprite_(TextureData::getInstance().getTexture(4001)),
	playerAnimation_(
		TextureData::getInstance().getTexture(1),
		sf::Vector2f(7.0f, 7.0f),
		4,
		0.25f),
	state_(State::Expanding),
	scale_(1.0f),
	minScale_(1.0f),
	maxScale_(1.2f),
	velScale_(0.05f)
{
	const float invInterfaceScale = 1.0f / Config::Interface::scale;

	const sf::Vector2f centerPosition(
		Config::Window::width * 0.5f * invInterfaceScale,
		Config::Window::height * 0.5f * invInterfaceScale);

	backdropSprite_.setOrigin(backdropSprite_.getSize() * 0.5f);
	backdropSprite_.setPosition(centerPosition);

	playerAnimation_.setOrigin(playerAnimation_.getSize() * 0.5f);
	playerAnimation_.setPosition(centerPosition);
}

void MainMenuBackdrop::update(float deltaTime)
{
	playerAnimation_.update(deltaTime);

	switch (state_)
	{
		case State::Expanding:
			scale_ += velScale_ * deltaTime;

			if (scale_ >= maxScale_)
			{
				scale_ = maxScale_;
				state_ = State::Contracting;
			}

			break;
		case State::Contracting:
			scale_ -= velScale_ * deltaTime;

			if (scale_ <= minScale_)
			{
				scale_ = minScale_;
				state_ = State::Expanding;
			}

			break;
	}

	const sf::Vector2f scale(scale_, scale_);

	backdropSprite_.setScale(scale);
	playerAnimation_.setScale(scale);
}

void MainMenuBackdrop::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	backdropSprite_.draw(target, states, scale);
	playerAnimation_.draw(target, states, scale);
}