#pragma once

class Event;
class Listener;

#include <queue>
#include <unordered_set>

class EventQueue
{
public:
	EventQueue(const EventQueue &) = delete;
	EventQueue(EventQueue &&) = delete;

	EventQueue &operator=(const EventQueue &) = delete;
	EventQueue &operator=(EventQueue &&) = delete;

	static EventQueue &getInstance();

	void send(Event *ev);
	void dispatch();

	void attach(Listener *listener);
	void detach(Listener *listener);
private:
	std::queue<Event *> events_;
	std::unordered_set<Listener *> listeners_;

	EventQueue();
	~EventQueue();
};