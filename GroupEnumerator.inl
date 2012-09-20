////////////////////////////////////////////////////////////////////////////////
// Filename:    GroupEnumerator.inl
// Description: ...
//
// Created:     2012-09-20 01:26:10
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T, typename TKey, typename TIter>
	class GroupEnumerator : public Enumerator<T>
	{
	public:
		typedef T ValueType;
		typedef TKey KeyType;
		typedef TIter Iterator;
		typedef GroupEnumerator<T, TKey, TIter> EnumeratorType;
		
		GroupEnumerator(Iterator first, Iterator last)
			: first(first), iter(first), last(last)
		{
		}

		KeyType GetKey()
		{
			return first->first;
		}
		
		bool MoveFirst() override
		{
			iter = first;
			return iter != last;
		}

		bool MoveNext() override
		{
			++iter;
			return iter != last;
		}

		ValueType GetCurrent() const override
		{
			return iter->second;
		}

	private:
		Iterator first;
		Iterator iter;
		Iterator last;
	};
}

