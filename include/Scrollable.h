#pragma once

#include <cstdint>

class Scrollable
{
public:
	Scrollable(uint64_t maxNumObjectsDisplayed);

	virtual ~Scrollable() = default;

	void updateOnMouseWheelScroll(float delta);
protected:
	uint64_t maxNumObjectsDisplayed_;
	uint64_t numObjectsDisplayed_;
	uint64_t numObjects_;
	uint64_t scrollIndex_;

	virtual void updateObjectPositions_() = 0;

	void scrollUp_();
	void scrollDown_();

	void setNumObjects_(uint64_t numObjects);
};