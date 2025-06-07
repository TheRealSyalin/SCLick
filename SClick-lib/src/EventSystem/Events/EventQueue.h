#pragma once

#include "pch.h"

namespace SClick::Core::EventSystem::Internal
{
#define uint_64 unsigned long long
#define empty 0ull

	class EventQueue
	{
	public:
		bool isEmpty = true;
	public:
		EventQueue() 
		{
			for (int i = 0; i < capacity; i++)
			{
				queue[i] = empty;
			}
		}

	public:

		void Enqueue(uint_64 p_entry)
		{
			if (count == capacity)
				return;

			isEmpty = false;

			if (queue[tail] == empty)
			{
				queue[tail] = p_entry;
				tail++;
				count++;

				if (tail >= capacity)
					tail = 0;
			}
		}

		uint_64 Dequeue()
		{
			uint_64 temp = queue[front];
			queue[front] = empty;

			front++;

			if (count > 0)
				count--;

			if (front >= capacity)
				front = 0;

			if (count == 0)
			{
				front = 0;
				tail = 0;
				isEmpty = true;
			}

			return temp;
		}

		uint_64 Peek()
		{
			return queue[front];
		}

		void Print()
		{
			for (int i = 0; i < capacity; i++)
			{
				std::cout << queue[i] << std::endl;
			}
		}

	private:
		static const int capacity = 125;
		uint_64 queue[capacity];

		int front = 0;
		int tail = 0;
		int count = 0;

	};
}
