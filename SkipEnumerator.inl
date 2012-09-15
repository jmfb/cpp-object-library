////////////////////////////////////////////////////////////////////////////////
// Filename:    SkipEnumerator.inl
// Description: ...
//
// Created:     2012-09-14 00:12:46
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T>
	class SkipEnumerator : public Enumerator<T>
	{
	public:
		typedef SkipEnumerator<T> ThisType;
		typedef T ValueType;
		typedef Enumerator<ValueType> InterfaceType;
		typedef std::size_t SizeType;

		SkipEnumerator(InterfaceType& iter, SizeType count)
			: iter(iter), skip(count)
		{
		}

		bool MoveFirst() override
		{
			auto count = 0ull;
			for (auto b = iter.MoveFirst(); b; b = iter.MoveNext())
				if (count++ == skip)
					return true;
			return false;
		}

		bool MoveNext() override
		{
			return iter.MoveNext();
		}

		ValueType GetCurrent() const override
		{
			return iter.GetCurrent();
		}

	private:
		InterfaceType& iter;
		SizeType skip;
	};

	template <typename T>
	inline SkipEnumerator<T> Enumerator<T>::Skip(std::size_t count)
	{
		return { *this, count };
	}
}

