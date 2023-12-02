#pragma once

#include "AlarmClock.h"
#include <SFML/Graphics/Texture.hpp>

template<typename T>
class Animation : public T
{
public:
	Animation(
		const sf::Texture &texture,
		const sf::Vector2f &frameSize,
		uint8_t numFrames,
		float frameSecs);

	virtual ~Animation() = default;

	void update(float deltaTime);

	void setRow(uint8_t row);

	uint8_t getCol() const;
	bool wasUpdated() const;
protected:
	AlarmClock frameClock_;

	sf::Vector2f frameSize_;

	uint8_t numFrames_;

	sf::Vector2<uint8_t> frameCoordinate_;

	bool wasUpdated_;

	void updateTexturePosition_();
};

template<typename T>
Animation<T>::Animation(
	const sf::Texture &texture,
	const sf::Vector2f &frameSize,
	uint8_t numFrames,
	float frameSecs)
	:
	T(texture, frameSize),
	frameClock_(frameSecs),
	frameSize_(frameSize),
	numFrames_(numFrames),
	frameCoordinate_(0, 0),
	wasUpdated_(false)
{
	this->updateTexturePosition_();
}

template<typename T>
void Animation<T>::update(float deltaTime)
{
	wasUpdated_ = false;

	frameClock_.update(deltaTime);

	if (frameClock_.isDone())
	{
		frameClock_.resetSoft();

		frameCoordinate_.x = (frameCoordinate_.x + 1) % numFrames_;

		this->updateTexturePosition_();

		wasUpdated_ = true;
	}
}

template<typename T>
void Animation<T>::setRow(uint8_t row)
{
	if (frameCoordinate_.y == row)
	{
		return;
	}

	frameCoordinate_.y = row;

	this->updateTexturePosition_();
}

template<typename T>
uint8_t Animation<T>::getCol() const
{
	return frameCoordinate_.x;
}

template<typename T>
bool Animation<T>::wasUpdated() const
{
	return wasUpdated_;
}

template<typename T>
void Animation<T>::Animation::updateTexturePosition_()
{
	this->setTexturePosition(
		sf::Vector2f(
			1.0f + frameCoordinate_.x * (frameSize_.x + 1.0f),
			1.0f + frameCoordinate_.y * (frameSize_.y + 1.0f)));
}