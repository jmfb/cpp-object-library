////////////////////////////////////////////////////////////////////////////////
// Filename:    SelectEnumerator.inl
// Description: ...
//
// Created:     2012-09-13 23:53:37
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T, typename TFunc>
	class SelectEnumerator : public Enumerator<decltype(std::declval<TFunc>()(std::declval<T>()))>
	{
	public:
		typedef SelectEnumerator<T, TFunc> ThisType;
		typedef T SourceType;
		typedef TFunc FunctionType;
		typedef decltype(std::declval<TFunc>()(std::declval<T>())) ValueType;
		typedef Enumerator<SourceType> SourceInterfaceType;
		typedef Enumerator<ValueType> InterfaceType;
	
		SelectEnumerator(SourceInterfaceType& iter, FunctionType func)
			: iter(iter), func(func)
		{
		}
	
		bool MoveFirst() override
		{
			return iter.MoveFirst();
		}
		
		bool MoveNext() override
		{
			return iter.MoveNext();
		}
		
		ValueType GetCurrent() const override
		{
			return func(iter.GetCurrent());
		}
	
	private:
		SourceInterfaceType& iter;
		FunctionType func;
	};
	
	template <typename T>
	template <typename TFunc>
	inline SelectEnumerator<T, TFunc> Enumerator<T>::Select(TFunc func)
	{
		return { *this, func };
	}
}

