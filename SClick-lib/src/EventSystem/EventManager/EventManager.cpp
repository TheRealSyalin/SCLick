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

	//eventCallback returns true if it successfully handles the event and should remove the event from the queue
	bool EventManager::HandleEvent(EventType type, const std::function<bool(unsigned short _1, unsigned short _2)> eventCallback)
	{
		auto event = collector.GetEventQueue().Peek();
		auto msg = DecodeEventType(event);

		if (msg != (unsigned int)type)
			return false;

		if (eventCallback(DecodeHighWord(event), DecodeLowWord(event)))
			collector.GetEventQueue().Dequeue();

		return true;
	}

	//eventCallback activates if the event we are looking for is in the queue but does not remove it from the queue
	bool EventManager::PassthroughEvent(EventType type, const std::function<void(unsigned short _1, unsigned short _2)> eventCallback)
	{
		auto event = collector.GetEventQueue().Peek();
		auto msg = DecodeEventType(event);

		if (msg != (unsigned int)type)
			return false;

		eventCallback(DecodeHighWord(event), DecodeLowWord(event));
		return true;
	}

    Utility::Vector2 EventManager::GetMouseButton(unsigned char mouseButton)
    {
		auto event = collector.GetEventQueue().Peek();
		auto msg = DecodeEventType(event);

		Utility::Vector2 mousePos{0,0};


		if (msg == ((unsigned int)EventType::MouseButtonDown | (unsigned int)mouseButton << 16))
		{
			unsigned int eventType = ((unsigned int)EventType::MouseButtonDown | (unsigned int)mouseButton << 16);
			HandleEvent((EventType)eventType, [&mousePos](unsigned short _1, unsigned short _2) {
				mousePos.SetX(_1);
				mousePos.SetY(_2);
				return true;
				});
		}
		
		return mousePos;
    }

	unsigned int EventManager::DecodeEventType(uint_64 event)
	{
		return static_cast<unsigned int>(event >> 32);
	}

	unsigned short EventManager::DecodeHighWord(uint_64 event)
	{
		return static_cast<unsigned short>(event >> 16);
	}

	unsigned short EventManager::DecodeLowWord(uint_64 event)
	{
		return static_cast<unsigned short>(event);
	}
}