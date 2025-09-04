#pragma once


namespace SClick::Core::DataType::ErrorHandling
{
	template<typename ReturnType, typename ErrorType>
	struct Result
	{
		Result(ReturnType);
		Result(ErrorType);
		Result(Result& p_other);
		~Result();
		operator bool();

		ReturnType GetValue();
		ErrorType GetError();

	private:

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
	inline Result<ReturnType, ErrorType>::Result(ReturnType t)
		:value(t), isError(false)
	{}

	template<typename ReturnType, typename ErrorType>
	inline Result<ReturnType, ErrorType>::Result(ErrorType e)
		:error(e), isError(true)
	{}

	template<typename ReturnType, typename ErrorType>
	Result<ReturnType, ErrorType>::Result(Result& p_other)
	{
		error = p_other.error;
		value = p_other.value;
		isError = p_other.isError;
	}

	template<typename ReturnType, typename ErrorType>
	Result<ReturnType, ErrorType>::~Result()
	{}

	template<typename ReturnType, typename ErrorType>
	Result<ReturnType, ErrorType>::operator bool()
	{
		return isError;
	}
	template<typename ReturnType, typename ErrorType>
	ReturnType Result<ReturnType, ErrorType>::GetValue()
	{
		return value;
	}
	template<typename ReturnType, typename ErrorType>
	ErrorType Result<ReturnType, ErrorType>::GetError()
	{
		return error;
	}
}