////////////////////////////////////////////////////////////////////////////////
// Filename:    GroupByEnumerator.inl
// Description: ...
//
// Created:     2012-09-20 00:56:51
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T, typename TFunc>
	class GroupByHelper
	{
	public:
		typedef T ValueType;
		typedef TFunc KeyFunctionType;
		typedef decltype(std::declval<KeyFunctionType>()(std::declval<ValueType>())) KeyType;
		typedef std::multimap<KeyType, ValueType> ContainerType;
		typedef typename ContainerType::iterator Iterator;
		typedef GroupEnumerator<ValueType, KeyType, Iterator> GroupEnumeratorType;
	};
	
	template <typename T, typename TFunc>
	class GroupByEnumerator : public Enumerator<typename GroupByHelper<T, TFunc>::GroupEnumeratorType>
	{
	public:
		typedef GroupByHelper<T, TFunc> Helper;
		typedef T SourceValueType;
		typedef Enumerator<SourceValueType> SourceInterfaceType;
		typedef TFunc KeyFunctionType;
		typedef typename Helper::KeyType KeyType;
		typedef typename Helper::ContainerType ContainerType;
		typedef typename Helper::Iterator Iterator;
		typedef typename Helper::GroupEnumeratorType ValueType;
		
		GroupByEnumerator(SourceInterfaceType& iter, KeyFunctionType keyFunc)
		{
			iter.ForEach([this, &keyFunc](T value){ groups.insert({ keyFunc(value), value }); });
		}
		
		bool MoveFirst() override
		{
			iter = groups.begin();
			if (iter == groups.end())
				return false;
			next = groups.upper_bound(iter->first);
			return true;
		}

		bool MoveNext() override
		{
			iter = next;
			if (iter == groups.end())
				return false;
			next = groups.upper_bound(iter->first);
			return true;
		}

		ValueType GetCurrent() const override
		{
			return { iter, next };
		}

	private:
		ContainerType groups;
		Iterator iter;
		Iterator next;
	};

	template <typename T>
	template <typename TFunc>
	inline GroupByEnumerator<T, TFunc> Enumerator<T>::GroupBy(TFunc func)
	{
		return { *this, func };
	}
}

