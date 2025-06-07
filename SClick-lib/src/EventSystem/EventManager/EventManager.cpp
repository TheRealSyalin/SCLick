#include "pch.h"

#include "EventManager.h"

namespace SClick::Core::EventSystem
{
	EventManager::EventManager()
	{}

	Internal::EventCollector& EventManager::GetEventCollector()
	{
		return collector;
	}

	void EventManager::PeekEvent(EventType type, std::function<void(unsigned short _1, unsigned short _2)> func)
	{
		auto event = collector.GetEventQueue().Peek();
		auto msg = DecodeEventType(event);

		if (msg != (unsigned int)type)
			return;

		collector.GetEventQueue().Dequeue();
			func(DecodeHighWord(event), DecodeLowWord(event));
	}

	unsigned int EventManager::DecodeEventType(uint_64 event)
	{
		return event >> 32;
	}

	unsigned short EventManager::DecodeHighWord(uint_64 event)
	{
		return event >> 16;
	}

	unsigned short EventManager::DecodeLowWord(uint_64 event)
	{
		return event;
	}
}