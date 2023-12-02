#include "Scrollable.h"
#include "Event.h"
#include "EventQueue.h"
#include <algorithm>

Scrollable::Scrollable(uint64_t maxNumObjectsDisplayed) :
	maxNumObjectsDisplayed_(maxNumObjectsDisplayed),
	numObjectsDisplayed_(0),
	numObjects_(0),
	scrollIndex_(0)
{}

void Scrollable::updateOnMouseWheelScroll(float delta)
{
	if (delta < 0.0f)
	{
		this->scrollDown_();
	}
	else if (delta > 0.0f)
	{
		this->scrollUp_();
	}
}

void Scrollable::scrollUp_()
{
	if (scrollIndex_ > 0)
	{
		--scrollIndex_;

		this->updateObjectPositions_();

		EventQueue::getInstance().send(
			new EventPlaySound(
				1011));
	}
}

void Scrollable::scrollDown_()
{
	if (scrollIndex_ + numObjectsDisplayed_ < numObjects_)
	{
		++scrollIndex_;

		this->updateObjectPositions_();

		EventQueue::getInstance().send(
			new EventPlaySound(
				1011));
	}
}

void Scrollable::setNumObjects_(uint64_t numObjects)
{
	numObjects_ = numObjects;
	numObjectsDisplayed_ = std::min(numObjects_, maxNumObjectsDisplayed_);

	if (scrollIndex_ + numObjectsDisplayed_ > numObjects_)
	{
		scrollIndex_ = numObjects_ - maxNumObjectsDisplayed_;

		this->updateObjectPositions_();
	}
}