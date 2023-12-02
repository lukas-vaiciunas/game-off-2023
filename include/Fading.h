#pragma once

#include "Living.h"
#include "AlarmClock.h"
#include <cstdint>

class Fading : public Living
{
public:
	Fading(float durationSecs);

	virtual ~Fading() = default;

	virtual void update(float deltaTime);
private:
	AlarmClock durationClock_;

	virtual void applyAlpha_(uint8_t alpha) = 0;
};