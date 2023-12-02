#include "AlarmClock.h"
#include <cmath>

AlarmClock::AlarmClock(float targetSecs) :
	targetSecs_(targetSecs),
	secs_(0.0f)
{}

void AlarmClock::update(float deltaTime)
{
	secs_ += deltaTime;
}

void AlarmClock::resetHard()
{
	secs_ = 0.0f;
}

void AlarmClock::resetSoft()
{
	secs_ = (this->isDone() ? fmodf(secs_, targetSecs_) : 0.0f);
}

float AlarmClock::getTargetSecs() const
{
	return targetSecs_;
}

float AlarmClock::getSecs() const
{
	return secs_;
}

bool AlarmClock::isDone() const
{
	return secs_ >= targetSecs_;
}