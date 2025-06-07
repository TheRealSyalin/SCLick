#pragma once

#include "pch.h"

#include "EventCollector.h"
#include "../Events/EventTypes.h"

namespace SClick::Core::EventSystem
{

	class EventManager
	{
	public:
		EventManager();

	public:
		Internal::EventCollector& GetEventCollector();

		void PeekEvent(EventType type, std::function<void(unsigned short _1, unsigned short _2)> func);
		

	private:
		Internal::EventCollector collector;

	private:
		unsigned int DecodeEventType(uint_64 event);
		unsigned short DecodeHighWord(uint_64 event);
		unsigned short DecodeLowWord(uint_64 event);
	};
}