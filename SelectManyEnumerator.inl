////////////////////////////////////////////////////////////////////////////////
// Filename:    SelectManyEnumerator.inl
// Description: ...
//
// Created:     2012-09-14 00:02:39
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T, typename TFunc>
	class SelectManyEnumerator : public Enumerator<typename decltype(std::declval<TFunc>()(std::declval<T>()))::ValueType>
	{
	public:
		typedef SelectManyEnumerator<T, TFunc> ThisType;
		typedef T SourceType;
		typedef TFunc FunctionType;
		typedef decltype(std::declval<TFunc>()(std::declval<T>())) ManyType;
		typedef std::shared_ptr<ManyType> ManyTypePtr;
		typedef typename ManyType::ValueType ValueType;
		typedef Enumerator<SourceType> SourceInterfaceType;
		typedef Enumerator<ValueType> InterfaceType;
	
		SelectManyEnumerator(SourceInterfaceType& iter, FunctionType func)
			: func(func), iter(iter)
		{
		}
	
		bool MoveFirst() override
		{
			if (iter.MoveFirst())
			{
				current = std::make_shared<ManyType>(func(iter.GetCurrent()));
				if (current->MoveFirst())
					return true;
				while (iter.MoveNext())
				{
					current = std::make_shared<ManyType>(func(iter.GetCurrent()));
					if (current->MoveFirst())
						return true;
				}
			}
			return false;
		}
	
		bool MoveNext() override
		{
			if (current->MoveNext())
				return true;
			while (iter.MoveNext())
			{
				current = std::make_shared<ManyType>(func(iter.GetCurrent()));
				if (current->MoveFirst())
					return true;
			}
			return false;
		}
	
		ValueType GetCurrent() const override
		{
			return current->GetCurrent();
		}
	
	private:
		SourceInterfaceType& iter;
		FunctionType func;
		ManyTypePtr current;
	};
	
	template <typename T>
	template <typename TFunc>
	inline SelectManyEnumerator<T, TFunc> Enumerator<T>::SelectMany(TFunc func)
	{
		return { *this, func };
	}
}

