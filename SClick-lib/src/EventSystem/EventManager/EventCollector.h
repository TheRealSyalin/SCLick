#pragma once

#include "pch.h"
#include "../Events/EventQueue.h"

namespace SClick::Core::EventSystem::Internal
{
	class EventCollector
	{

	public:
		EventCollector()
			:queue()
		{}

		
		void CollectorCallback(unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord)
		{
			queue.Enqueue((uint_64)eventTypeWord << 32 | (uint_64)highWord << 16 | lowWord);
		}

	public:
		EventQueue& GetEventQueue()
		{
			return queue;
		}

	private:
		EventQueue queue;
	};
}