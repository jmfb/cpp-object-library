#pragma once
#include <tuple>

template <typename TName, typename... TProperties>
class Entity
{
public:
	typedef TName NameType;
	typedef std::tuple<TProperties...> PropertyTuple;
	typedef std::tuple<typename TProperties::StorageType...> PropertyStorageTuple;
	typedef std::tuple<typename TProperties::Type...> PropertyTypeTuple;
	typedef std::tuple<typename TProperties::NameType...> PropertyNameTuple;
};
