////////////////////////////////////////////////////////////////////////////////
// Filename:    RepeatEnumerator.inl
// Description: ...
//
// Created:     2012-09-13 23:16:21
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T>
	class RepeatEnumerator : public Enumerator<T>
	{
	public:
		typedef RepeatEnumerator<T> ThisType;
		typedef T ValueType;
		typedef Enumerator<ValueType> InterfaceType;
		typedef std::size_t SizeType;

		RepeatEnumerator(ValueType value, SizeType count)
			: value(value), count(count), index(0)
		{
		}

		bool MoveFirst() override
		{
			index = 0;
			return index < count;
		}

		bool MoveNext() override
		{
			++index;
			return index < count;
		}

		ValueType GetCurrent() const override
		{
			return value;
		}

	private:
		ValueType value;
		SizeType count;
		SizeType index;
	};

	template <typename T>
	inline RepeatEnumerator<T> Repeat(T value, std::size_t count)
	{
		return { value, count };
	}
}

