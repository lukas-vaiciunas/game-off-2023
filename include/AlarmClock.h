#pragma once

class AlarmClock
{
public:
	AlarmClock(float targetSecs);

	void update(float deltaTime);

	void resetHard();
	void resetSoft();

	float getTargetSecs() const;
	float getSecs() const;
	bool isDone() const;
private:
	float targetSecs_;
	float secs_;
};