#include "Fading.h"

Fading::Fading(float durationSecs) :
	durationClock_(durationSecs)
{}

void Fading::update(float deltaTime)
{
	durationClock_.update(deltaTime);

	const float durationRatio = durationClock_.getSecs() / durationClock_.getTargetSecs();
	const float durationThreshold = 0.8f;

	if (durationRatio > durationThreshold)
	{
		const float alphaMod = (1.0f - durationRatio) / (1.0f - durationThreshold);

		const uint8_t alpha = static_cast<uint8_t>(255 * alphaMod);

		this->applyAlpha_(alpha);
	}

	if (durationClock_.isDone())
	{
		isLive_ = false;
	}
}