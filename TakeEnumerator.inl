////////////////////////////////////////////////////////////////////////////////
// Filename:    TakeEnumerator.inl
// Description: ...
//
// Created:     2012-09-14 00:12:38
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T>
	class TakeEnumerator : public Enumerator<T>
	{
	public:
		typedef TakeEnumerator<T> ThisType;
		typedef T ValueType;
		typedef Enumerator<ValueType> InterfaceType;
		typedef std::size_t SizeType;

		TakeEnumerator(InterfaceType& iter, SizeType count)
			: iter(iter), take(count), count(0)
		{
		}

		bool MoveFirst() override
		{
			count = 0;
			return iter.MoveFirst() && count < take;
		}

		bool MoveNext() override
		{
			return iter.MoveNext() && ++count < take;
		}

		ValueType GetCurrent() const override
		{
			return iter.GetCurrent();
		}

	private:
		InterfaceType& iter;
		SizeType take;
		SizeType count;
	};

	template <typename T>
	inline TakeEnumerator<T> Enumerator<T>::Take(std::size_t count)
	{
		return { *this, count };
	}
}

