////////////////////////////////////////////////////////////////////////////////
// Filename:    ZipEnumerator.inl
// Description: ...
//
// Created:     2012-09-14 00:29:06
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T, typename TSecond, typename TFunc>
	class ZipEnumerator : public Enumerator<decltype(std::declval<TFunc>()(std::declval<T>()))>
	{
	public:
		typedef ZipEnumerator<T, TSecond, TFunc> ThisType;
		typedef T FirstSourceType;
		typedef TSecond SecondSourceType;
		typedef TFunc FunctionType;
		typedef decltype(std::declval<TFunc>()(std::declval<T>())) ValueType;
		typedef Enumerator<FirstSourceType> FirstSourceInterfaceType;
		typedef Enumerator<SecondSourceType> SecondSourceInterfaceType;
		typedef Enumerator<ValueType> InterfaceType;
	
		ZipEnumerator(FirstSourceInterfaceType& first, SecondSourceInterfaceType& second, FunctionType transform)
			: first(first), second(second), transform(transform)
		{
		}
	
		bool MoveFirst() override
		{
			return first.MoveFirst() && second.MoveFirst();
		}
		
		bool MoveNext() override
		{
			return first.MoveNext() && second.MoveNext();
		}
		
		ValueType GetCurrent() const override
		{
			return transform(first.GetCurrent(), second.GetCurrent());
		}
	
	private:
		FirstSourceInterfaceType& first;
		SecondSourceInterfaceType& second;
		FunctionType transform;
	};
	
	template <typename T>
	template <typename TSecond>
	inline ZipEnumerator<T, TSecond, std::pair<T, TSecond>(T, TSecond)> Enumerator<T>::Zip(Enumerator<TSecond>& second)
	{
		return { *this, second, &std::make_pair<T, TSecond> };
	}
	
	template <typename T>
	template <typename TSecond, typename TFunc>
	inline ZipEnumerator<T, TSecond, TFunc> Enumerator<T>::Zip(Enumerator<TSecond>& second, TFunc transform)
	{
		return(ZipEnumerator<T, TSecond, TFunc>(*this, second, transform));
	}
}

