////////////////////////////////////////////////////////////////////////////////
// Filename:    ConcatEnumerator.inl
// Description: ...
//
// Created:     2012-09-14 00:23:47
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T, typename TEnum>
	class ConcatEnumerator : public Enumerator<T>
	{
	public:
		typedef ConcatEnumerator<T, TEnum> ThisType;
		typedef T ValueType;
		typedef TEnum SecondInterfaceType;
		typedef Enumerator<T> InterfaceType;
	
		ConcatEnumerator(InterfaceType& first, SecondInterfaceType second)
			: first(first), second(second), isSecond(false)
		{
		}
	
		bool MoveFirst() override
		{
			isSecond = false;
			if (first.MoveFirst())
				return true;
			isSecond = true;
			return second.MoveFirst();
		}
		
		bool MoveNext() override
		{
			if (isSecond)
				return second.MoveNext();
			if (first.MoveNext())
				return true;
			isSecond = true;
			return second.MoveFirst();
		}
	
		ValueType GetCurrent() const override
		{
			return isSecond ? second.GetCurrent() : first.GetCurrent();
		}
	
	private:
		InterfaceType& first;
		SecondInterfaceType second;
		bool isSecond;
	};
	
	template <typename T>
	template <typename TEnum>
	inline ConcatEnumerator<T, TEnum> Enumerator<T>::Concat(TEnum rhs)
	{
		return { *this, rhs };
	}
}

