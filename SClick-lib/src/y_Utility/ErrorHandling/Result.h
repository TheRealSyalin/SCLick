#pragma once

namespace SClick::Core::DataType::ErrorHandling
{
	template<typename ReturnType, typename ErrorType>
	struct Result
	{
		Result();
		Result(Result& p_other);
		~Result();

		union
		{
			ErrorType error;
			ReturnType value;
		};

		bool isError;
	};
}

namespace SClick::Core::DataType::ErrorHandling
{
	template<typename ReturnType, typename ErrorType>
	Result<ReturnType, ErrorType>::Result()
		:isError(false) {
	}

	template<typename ReturnType, typename ErrorType>
	Result<ReturnType, ErrorType>::Result(Result& p_other)
	{
		error = p_other.error;
		value = p_other.value;
		isError = p_other.isError;
	}

	template<typename ReturnType, typename ErrorType>
	Result<ReturnType, ErrorType>::~Result()
	{
	}
}