////////////////////////////////////////////////////////////////////////////////
// Filename:    StaticCastEnumerator.inl
// Description: ...
//
// Created:     2012-09-14 00:23:33
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T, typename TCast>
	class StaticCastEnumerator : public Enumerator<TCast>
	{
	public:
		typedef StaticCastEnumerator<T, TCast> ThisType;
		typedef T SourceType;
		typedef TCast ValueType;
		typedef Enumerator<SourceType> SourceInterfaceType;
		typedef Enumerator<ValueType> InterfaceType;
	
		StaticCastEnumerator(SourceInterfaceType& iter)
			: iter(iter)
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
			return static_cast<ValueType>(iter.GetCurrent());
		}
	
	private:
		SourceInterfaceType& iter;
	};
	
	template <typename T>
	template <typename TCast>
	inline StaticCastEnumerator<T, TCast> Enumerator<T>::Cast()
	{
		return { *this };
	}
}

