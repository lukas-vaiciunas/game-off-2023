#pragma once

class Event;

#include "EventType.h"
#include <unordered_set>

class Listener
{
public:
	Listener(const std::unordered_set<EventType> acceptedEventTypes);

	virtual ~Listener();

	virtual void onEvent(const Event &ev) = 0;

	bool acceptsEventType(EventType type) const;
private:
	std::unordered_set<EventType> acceptedEventTypes_;
};