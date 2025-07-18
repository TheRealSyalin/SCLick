#pragma once

#include <functional>

#include "EventCollector.h"
#include "../Events/EventTypes.h"
#include "../../y_Utility/Utility.h"

namespace SClick::Core::EventSystem
{

	class EventManager
	{
	public:
		EventManager();

	public:
		Internal::EventCollector& GetEventCollector();

		//eventCallback returns true if it successfully handles the event and should remove the event from the queue
        bool HandleEvent(EventType type, std::function<bool(unsigned short _1, unsigned short _2)> eventCallback);

		//eventCallback activates if the event we are looking for is in the queue but does not remove it from the queue
		bool PassthroughEvent(EventType type, std::function<void(unsigned short _1, unsigned short _2)> eventCallback);
		
		Utility::Vector2 GetMouseButton(unsigned char mouseButton);

	private:
		Internal::EventCollector collector;

	private:
		unsigned int DecodeEventType(uint_64 event);
		unsigned short DecodeHighWord(uint_64 event);
		unsigned short DecodeLowWord(uint_64 event);
	};
}