#pragma once

#include <array>

namespace SClick::Core::DataType::ErrorHandling
{
	template<std::size_t size>
	class TemplateFriendlyString
	{
	private:
		char string[size];

	public:
		TemplateFriendlyString()
		{
			for (int i = 0; i < size; i++)
			{
				string[i] = ' ';
			}
		}

	public:
		void Print()
		{
			for (char c : string)
			{
				if (c == '\0')
					break;
				std::cout << c;
			}
			std::cout << "\n";
		}

		TemplateFriendlyString& operator=(TemplateFriendlyString& p_string)
		{
			std::memcpy(this, &p_string, size);
			return *this;
		}

		void operator=(const char* p_string)
		{
			auto len = strlen(p_string) + 1;
			if (len > size)
				return;

			std::memcpy(&string, p_string, len);
		}
	};
}
