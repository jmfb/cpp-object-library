#pragma once
#include "Entity.h"
#include "TypeInfoHelper.h"
#include "IndexByName.h"

template <typename T>
class EntityInstance
{
public:
	typedef T EntityType;
	typedef typename T::NameType NameType;
	typedef typename T::PropertyTuple PropertyTuple;
	typedef typename T::PropertyStorageTuple PropertyStorageTuple;
	typedef typename T::PropertyTypeTuple PropertyTypeTuple;
	typedef typename T::PropertyNameTuple PropertyNameTuple;
	
	template <typename TName>
	auto Get() -> typename std::tuple_element<IndexByName<0, TName, PropertyNameTuple>::Index, PropertyStorageTuple>::type&
	{
		return std::get<IndexByName<0, TName, PropertyNameTuple>::Index>(mValue);
	}
	
	template <typename TName>
	auto Get() const -> const typename std::tuple_element<IndexByName<0, TName, PropertyNameTuple>::Index, PropertyStorageTuple>::type&
	{
		return std::get<IndexByName<0, TName, PropertyNameTuple>::Index>(mValue);
	}
	
private:
	PropertyStorageTuple mValue;
};

template <typename TName, typename... TProperties>
class TypeInfoHelper<Entity<TName, TProperties...>>
{
public:
	typedef EntityInstance<Entity<TName, TProperties...>> StorageType;
};
