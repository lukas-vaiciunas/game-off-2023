#include "OpenedEyeballState.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"
#include "Config.h"

OpenedEyeballState::OpenedEyeballState(
	const sf::Vector2f &position,
	const std::string &textString)
	:
	EyeballState(),
	Shakable(0.25f, 1.0f),
	animation_(
		TextureData::getInstance().getTexture(902),
		sf::Vector2f(7.0f, 7.0f),
		4,
		0.5f),
	text_(),
	textString_(textString),
	writeClock_(0.025f),
	writeIndex_(0),
	durationClock_(5.0f),
	position_(position)
{
	const sf::Vector2f &animationSize = animation_.getSize();
	const sf::Vector2f halfAnimationSize = animationSize * 0.5f;

	animation_.setOrigin(halfAnimationSize);
	animation_.setPosition(position_ + halfAnimationSize);

	text_.setCharacterSize(Config::Text::Size::medium);
	text_.setFillColor(sf::Color(225, 225, 225));
	text_.setOutlineColor(sf::Color(0, 0, 0));
	text_.setInterfacePosition(
		sf::Vector2f(
			position.x + animationSize.x + 2.0f,
			position.y + halfAnimationSize.y));

	this->shake_(1.0f);
}

void OpenedEyeballState::update(float deltaTime)
{
	Shakable::update(deltaTime);

	animation_.setPosition(position_ + animation_.getSize() * 0.5f + offset_);

	animation_.update(deltaTime);

	if (writeIndex_ <= textString_.size())
	{
		writeClock_.update(deltaTime);

		if (writeClock_.isDone())
		{
			writeClock_.resetSoft();

			++writeIndex_;

			this->setTextString_(textString_.substr(0, writeIndex_));
		}
	}
	else
	{
		durationClock_.update(deltaTime);

		if (durationClock_.isDone())
		{
			EventQueue::getInstance().send(
				new EventCloseEyeball());
		}
	}
}

bool OpenedEyeballState::isHovered() const
{
	return false;
}

void OpenedEyeballState::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	animation_.draw(target, states, scale);
	text_.draw(target, states, scale);
}

void OpenedEyeballState::setTextString_(const std::string &string)
{
	text_.setString(string);

	const sf::FloatRect textLocalBounds = text_.getLocalBounds();

	text_.setOrigin(
		textLocalBounds.left,
		textLocalBounds.top + textLocalBounds.height * 0.5f);
}