#pragma once
#include <type_traits>
#include <tuple>

template <unsigned long TIndex, typename TName, typename... T>
class IndexByName
{
};

template <unsigned long TIndex, typename TName, typename TFirst, typename... TRest>
class IndexByName<TIndex, TName, std::tuple<TFirst, TRest...>>
{
public:
	enum { Index = std::is_same<TName, TFirst>::value ? TIndex : IndexByName<TIndex + 1, TName, std::tuple<TRest...>>::Index };
};

template <unsigned long TIndex, typename TName>
class IndexByName<TIndex, TName, std::tuple<>>
{
public:
	enum { Index = -1 };
};
