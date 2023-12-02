#include "Shakable.h"
#include "Random.h"

Shakable::Shakable(float maxOffset, float traumaDecay) :
	offset_(0.0f, 0.0f),
	maxOffset_(maxOffset),
	trauma_(0.0f),
	traumaDecay_(traumaDecay)
{}

void Shakable::update(float deltaTime)
{
	if (trauma_ == 0.0f)
	{
		return;
	}

	std::mt19937 &eng = Random::getInstance().getEngine();
	std::uniform_real_distribution<float> directionDis(-1.0f, 1.0f);

	const float offset = maxOffset_ * trauma_;

	offset_.x = offset * directionDis(eng);
	offset_.y = offset * directionDis(eng);

	trauma_ *= traumaDecay_;
}

void Shakable::shake_(float trauma)
{
	trauma_ += trauma;

	if (trauma_ > 1.0f)
	{
		trauma_ = 1.0f;
	}
}