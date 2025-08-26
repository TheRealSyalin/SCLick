#include "pch.h"

#include "EventManager.h"


namespace SClick::Core::EventSystem
{
	EventManager::EventManager()
		:m_eventCallback(std::bind(
			&SClick::Core::EventSystem::EventManager::PostEvent,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3))
	{}

	//eventCallback returns true if it successfully handles the event and should remove the event from the queue
	bool EventManager::HandleEvent(EventType type, const std::function<bool(unsigned short _1, unsigned short _2)> eventCallback)
	{ 
		std::uint64_t event = queue.Peek();
		unsigned int msg = DecodeEventType(event);

		if (msg != (unsigned int)type)
			return false;

		if (eventCallback(DecodeHighWord(event), DecodeLowWord(event)))
			queue.Dequeue();

		return true;
	}

	//eventCallback activates if the event we are looking for is in the queue but does not remove it from the queue
	bool EventManager::PassthroughEvent(EventType type, const std::function<void(unsigned short _1, unsigned short _2)> eventCallback)
	{
		std::uint64_t event = queue.Peek();
		unsigned int msg = DecodeEventType(event);

		if (msg != (unsigned int)type)
			return false;

		eventCallback(DecodeHighWord(event), DecodeLowWord(event));
		return true;
	}

	EventCallback& EventManager::GetEventCallback()
	{
		return m_eventCallback;
	}

    DataType::Vector2 EventManager::GetMouseButtonDown(MouseButtons mouseButton)
    {
		std::uint64_t event = queue.Peek();
		unsigned int msg = DecodeEventType(event);

		DataType::Vector2 mousePos{0,0};


		if (msg == ((unsigned int)EventType::MouseButtonDown | (unsigned int)mouseButton << 16))
		{
			unsigned int eventType = ((unsigned int)EventType::MouseButtonDown | (unsigned int)mouseButton << 16);
			PassthroughEvent((EventType)eventType, [&mousePos](unsigned short _1, unsigned short _2) {
				mousePos.x = _1;
				mousePos.y = _2;
				return true;
				});
		}
		
		return mousePos;
    }

	DataType::Vector2 EventManager::GetMouseButtonUp(MouseButtons mouseButton)
	{
		auto event = queue.Peek();
		auto msg = DecodeEventType(event);

		DataType::Vector2 mousePos{ 0,0 };


		if (msg == ((unsigned int)EventType::MouseButtonUp | (unsigned int)mouseButton << 16))
		{
			unsigned int eventType = ((unsigned int)EventType::MouseButtonUp | (unsigned int)mouseButton << 16);
			PassthroughEvent((EventType)eventType, [&mousePos](unsigned short _1, unsigned short _2) {
				mousePos.x = _1;
				mousePos.y = _2;
				return true;
				});
		}

		return mousePos;
	}

	std::tuple<MouseButtons, DataType::Vector2> EventManager::GetMouseButton()
	{
		std::uint64_t event = queue.Peek();
		unsigned int msg = DecodeEventType(event);

		unsigned char mouseButton = msg >> 16;
		unsigned int eventType = msg & 0b00000000000000001111111111111111;

		DataType::Vector2 mousePos{ 0,0 };


		if (eventType == (unsigned int)EventType::MouseButtonUp || eventType == (unsigned int)EventType::MouseButtonDown)
		{
			PassthroughEvent((EventType)(eventType | (unsigned int)mouseButton << 16), [&mousePos](unsigned short _1, unsigned short _2) {
				mousePos.x = _1;
				mousePos.y = _2;
				return true;
				});
		}
		return { (MouseButtons)mouseButton, mousePos };
	}

	Internal::EventQueue& EventManager::GetEventQueue()
	{
		return queue;
	}

	unsigned int EventManager::DecodeEventType(std::uint64_t event)
	{
		return static_cast<unsigned int>(event >> 32);
	}

	unsigned short EventManager::DecodeHighWord(std::uint64_t event)
	{
		return static_cast<unsigned short>(event >> 16);
	}

	unsigned short EventManager::DecodeLowWord(std::uint64_t event)
	{
		return static_cast<unsigned short>(event);
	}

	void EventManager::PostEvent(unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord)
	{
		queue.Enqueue((std::uint64_t)eventTypeWord << 32 | (std::uint64_t)highWord << 16 | lowWord);
	}
}