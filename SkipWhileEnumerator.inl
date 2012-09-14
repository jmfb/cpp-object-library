////////////////////////////////////////////////////////////////////////////////
// Filename:    SkipWhileEnumerator.inl
// Description: ...
//
// Created:     2012-09-14 00:12:43
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T, typename TFunc>
	class SkipWhileEnumerator : public Enumerator<T>
	{
	public:
		typedef SkipWhileEnumerator<T, TFunc> ThisType;
		typedef T ValueType;
		typedef TFunc FunctionType;
		typedef Enumerator<ValueType> InterfaceType;
	
		SkipWhileEnumerator(InterfaceType& iter, FunctionType func)
			: iter(iter), func(func)
		{
		}
	
		bool MoveFirst() override
		{
			for (auto b = iter.MoveFirst(); b; b = iter.MoveNext())
				if (!func(iter.GetCurrent()))
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
		FunctionType func;
	};
	
	template <typename T>
	template <typename TFunc>
	inline SkipWhileEnumerator<T, TFunc> Enumerator<T>::SkipWhile(TFunc func)
	{
		return { *this, func };
	}
}

