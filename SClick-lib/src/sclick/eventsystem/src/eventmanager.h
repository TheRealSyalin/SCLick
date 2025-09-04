#pragma once

#include <functional>
#include <tuple>

#include "eventqueue.h"
#include "eventtypes.h"
#include "sclick/datatypes/datatypes.h"

namespace SClick::Core::EventSystem
{

	using EventCallback = std::function<void(unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord)>;

	class EventManager 
	{
	public:
		EventManager();

	public:
		//eventCallback returns true if it successfully handles the event and should remove the event from the queue
        bool HandleEvent(EventType type, std::function<bool(unsigned short _1, unsigned short _2)> eventCallback);

		//eventCallback activates if the event we are looking for is in the queue but does not remove it from the queue
		bool PassthroughEvent(EventType type, std::function<void(unsigned short _1, unsigned short _2)> eventCallback);
		
		EventCallback& GetEventCallback();
		DataType::Vector2 GetMouseButtonDown(MouseButtons mouseButton);
		DataType::Vector2 GetMouseButtonUp(MouseButtons mouseButton);
		std::tuple<MouseButtons, DataType::Vector2> GetMouseButton();
		Internal::EventQueue& GetEventQueue();

	private:
		alignas(64) Internal::EventQueue queue;
		EventCallback m_eventCallback;

	private:
		unsigned int DecodeEventType(std::uint64_t event);
		unsigned short DecodeHighWord(std::uint64_t event);
		unsigned short DecodeLowWord(std::uint64_t event);

		void PostEvent(unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord);
	};
}