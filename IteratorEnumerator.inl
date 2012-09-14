////////////////////////////////////////////////////////////////////////////////
// Filename:    IteratorEnumerator.inl
// Description: ...
//
// Created:     2012-09-13 23:29:34
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T>
	class IteratorEnumerator : public Enumerator<decltype(*std::declval<T>())>
	{
	public:
		typedef IteratorEnumerator<T> ThisType;
		typedef T IteratorType;
		typedef decltype(*std::declval<T>()) ValueType;
		typedef Enumerator<ValueType> InterfaceType;
	
		IteratorEnumerator(IteratorType first, IteratorType last)
			: begin(first), iter(first), end(last)
		{
		}
	
		bool MoveFirst() override
		{
			iter = begin;
			return iter != end;
		}
	
		bool MoveNext() override
		{
			++iter;
			return iter != end;
		}
	
		ValueType GetCurrent() const override
		{
			return *iter;
		}
	
	private:
		IteratorType begin;
		IteratorType iter;
		IteratorType end;
	};
	
	template <typename T>
	inline IteratorEnumerator<typename T::iterator> From(T& container)
	{
		return { container.begin(), container.end() };
	}

	template <typename T>
	inline IteratorEnumerator<typename T::const_iterator> From(const T& container)
	{
		return { container.begin(), container.end() };
	}
	
	template <typename T>
	inline IteratorEnumerator<typename T::const_iterator> FromConst(const T& container)
	{
		return { container.cbegin(), container.cend() };
	}
	
	template <typename T>
	inline IteratorEnumerator<typename T::reverse_iterator> FromReverse(T& container)
	{
		return { container.rbegin(), container.rend() };
	}
	
	template <typename T>
	inline IteratorEnumerator<typename T::const_reverse_iterator> FromReverse(const T& container)
	{
		return { container.rbegin(), container.rend() };
	}
	
	template <typename T>
	inline IteratorEnumerator<typename T::const_reverse_iterator> FromConstReverse(const T& container)
	{
		return { container.crbegin(), container.crend() };
	}
}

