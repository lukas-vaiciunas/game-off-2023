#include "Listener.h"
#include "EventQueue.h"

Listener::Listener(const std::unordered_set<EventType> acceptedEventTypes) :
	acceptedEventTypes_(acceptedEventTypes)
{
	EventQueue::getInstance().attach(this);
}

Listener::~Listener()
{
	EventQueue::getInstance().detach(this);
}

bool Listener::acceptsEventType(EventType type) const
{
	return acceptedEventTypes_.find(type) != acceptedEventTypes_.end();
}