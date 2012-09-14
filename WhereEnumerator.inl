////////////////////////////////////////////////////////////////////////////////
// Filename:    WhereEnumerator.inl
// Description: ...
//
// Created:     2012-09-13 23:47:31
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T, typename TFunc>
	class WhereEnumerator : public Enumerator<T>
	{
	public:
		typedef WhereEnumerator<T, TFunc> ThisType;
		typedef T ValueType;
		typedef TFunc FunctionType;
		typedef Enumerator<ValueType> InterfaceType;
	
		WhereEnumerator(InterfaceType& iter, FunctionType func)
			: iter(iter), func(func)
		{
		}
	
		bool MoveFirst() override
		{
			for (auto b = iter.MoveFirst(); b; b = iter.MoveNext())
				if (func(iter.GetCurrent()))
					return true;
			return false;
		}
	
		bool MoveNext() override
		{
			for (auto b = iter.MoveNext(); b; b = iter.MoveNext())
				if (func(iter.GetCurrent()))
					return true;
			return false;
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
	inline WhereEnumerator<T, TFunc> Enumerator<T>::Where(TFunc func)
	{
		return { *this, func };
	}
}

