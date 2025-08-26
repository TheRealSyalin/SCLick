#pragma once
#include <iostream>
#include <cstdint>

//TODO not thread safe

namespace SClick::Core::EventSystem::Internal
{
	class EventQueue
	{
	
	public:
		EventQueue() 
		{
			for (int i = 0; i < capacity; i++)
			{
				queue[i] = 0;
			}
		}

	public:

		void Enqueue(std::uint64_t p_entry)
		{
			if (count == capacity)
			{
				std::cout << "QUEUE FULL \n";
				return;
			}

			if (queue[tail] == 0)
			{
				queue[tail] = p_entry;
				tail++;
				count++;

				if (tail >= capacity)
					tail = 0;
			}
		}

		std::uint64_t Dequeue()
		{
			std::uint64_t temp = queue[front];
			queue[front] = 0;

			front++;

			if (count > 0)
				count--;

			if (front >= capacity)
				front = 0;

			if (count == 0)
			{
				front = 0;
				tail = 0;
			}

			return temp;
		}

		void FreeQueue()
		{
			for (int i = 0; i < capacity; i++)
			{
				queue[i] = 0;
			}

			front = 0;
			tail = 0;
			count = 0;
		}

		std::uint64_t Peek()
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

		int Size()
		{
			return count;
		}

		const bool IsEmpty() const
		{
			return count == 0;
		}

	private:
		static const int capacity = 6;
		alignas(64) std::uint64_t queue[capacity];
		int front = 0;
		int tail = 0;
		int count = 0;
	};
}
