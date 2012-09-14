////////////////////////////////////////////////////////////////////////////////
// Filename:    TakeWhileEnumerator.inl
// Description: ...
//
// Created:     2012-09-14 00:12:20
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T, typename TFunc>
	class TakeWhileEnumerator : public Enumerator<T>
	{
	public:
		typedef TakeWhileEnumerator<T, TFunc> ThisType;
		typedef T ValueType;
		typedef TFunc FunctionType;
		typedef Enumerator<ValueType> InterfaceType;
	
		TakeWhileEnumerator(InterfaceType& iter, FunctionType func)
			: iter(iter), func(func)
		{
		}
	
		bool MoveFirst() override
		{
			return iter.MoveFirst() && func(iter.GetCurrent());
		}
	
		bool MoveNext() override
		{
			return iter.MoveNext() && func(iter.GetCurrent());
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
	inline TakeWhileEnumerator<T, TFunc> Enumerator<T>::TakeWhile(TFunc func)
	{
		return { *this, func };
	}
}

