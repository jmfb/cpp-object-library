////////////////////////////////////////////////////////////////////////////////
// Filename:    RangeEnumerator.inl
// Description: ...
//
// Created:     2012-09-13 23:23:16
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T>
	class RangeEnumerator : public Enumerator<T>
	{
	public:
		typedef RangeEnumerator<T> ThisType;
		typedef T ValueType;
		typedef Enumerator<ValueType> InterfaceType;
		typedef std::size_t SizeType;

		RangeEnumerator(ValueType first, SizeType count, ValueType step)
			: first(first), value(first), step(step), count(count), index(0)
		{
		}

		bool MoveFirst() override
		{
			value = first;
			index = 0;
			return count > 0;
		}

		bool MoveNext() override
		{
			value += step;
			++index;
			return index < count;
		}

		ValueType GetCurrent() const override
		{
			return value;
		}

	private:
		ValueType first;
		ValueType value;
		ValueType step;
		SizeType count;
		SizeType index;
	};

	template <typename T>
	inline RangeEnumerator<T> Range(T first, std::size_t count)
	{
		return { first, count, 1 };
	}

	template <typename T>
	inline RangeEnumerator<T> Range(T first, std::size_t count, T step)
	{
		return { first, count, step };
	}
}

