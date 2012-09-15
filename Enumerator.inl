////////////////////////////////////////////////////////////////////////////////
// Filename:    Enumerator.inl
// Description: ...
//
// Created:     2012-09-13 22:45:42
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Enumerator.h"

namespace Linq
{
	template <typename T>
	template <typename TFunc>
	inline TFunc Enumerator<T>::ForEach(TFunc func)
	{
		for (auto b = MoveFirst(); b; b = MoveNext())
			func(GetCurrent());
		return func;
	}

	template <typename T>
	inline T Enumerator<T>::Single()
	{
		if (!MoveFirst())
			RaiseEmpty();
		auto first = GetCurrent();
		if (MoveNext())
			RaiseMultiple();
		return first;
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::Single(TFunc func)
	{
		return Where(func).Single();
	}

	template <typename T>
	inline T Enumerator<T>::SingleOrDefault()
	{
		return SingleOrDefault(T());
	}

	template <typename T>
	inline T Enumerator<T>::SingleOrDefault(T def)
	{
		if (!MoveFirst())
			return def;
		auto first = GetCurrent();
		if (MoveNext())
			RaiseMultiple();
		return first;
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::SingleOrDefault(TFunc func)
	{
		return SingleOrDefault(func, T());
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::SingleOrDefault(TFunc func, T def)
	{
		return Where(func).SingleOrDefault(def);
	}

	template <typename T>
	inline T Enumerator<T>::First()
	{
		if (!MoveFirst())
			RaiseEmpty();
		return GetCurrent();
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::First(TFunc func)
	{
		return Where(func).First();
	}

	template <typename T>
	inline T Enumerator<T>::FirstOrDefault()
	{
		return FirstOrDefault(T());
	}

	template <typename T>
	inline T Enumerator<T>::FirstOrDefault(T def)
	{
		if (!MoveFirst())
			return def;
		return GetCurrent();
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::FirstOrDefault(TFunc func)
	{
		return FirstOrDefault(func, T());
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::FirstOrDefault(TFunc func, T def)
	{
		return Where(func).FirstOrDefault(def);
	}

	template <typename T>
	inline T Enumerator<T>::Last()
	{
		if (!MoveFirst())
			RaiseEmpty();
		for (;;)
		{
			auto last = GetCurrent();
			if (!MoveNext())
				return last;
		}
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::Last(TFunc func)
	{
		return Where(func).Last();
	}

	template <typename T>
	inline T Enumerator<T>::LastOrDefault()
	{
		return LastOrDefault(T());
	}

	template <typename T>
	inline T Enumerator<T>::LastOrDefault(T def)
	{
		if (!MoveFirst())
			return def;
		for (;;)
		{
			auto last = GetCurrent();
			if (!MoveNext())
				return last;
		}
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::LastOrDefault(TFunc func)
	{
		return LastOrDefault(func, T());
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::LastOrDefault(TFunc func, T def)
	{
		return Where(func).LastOrDefault(def);
	}

	template <typename T>
	inline T Enumerator<T>::ElementAt(std::size_t position)
	{
		auto count = 0ull;
		for (auto b = MoveFirst(); b; b = MoveNext())
			if (count++ == position)
				return GetCurrent();
		RaiseIndex();
	}

	template <typename T>
	inline T Enumerator<T>::ElementAtOrDefault(std::size_t position)
	{
		return ElementAtOrDefault(position, T());
	}

	template <typename T>
	inline T Enumerator<T>::ElementAtOrDefault(std::size_t position, T def)
	{
		auto count = 0ull;
		for (auto b = MoveFirst(); b; b = MoveNext())
			if (count++ == position)
				return GetCurrent();
		return def;
	}

	template <typename T>
	inline T Enumerator<T>::Sum()
	{
		T result { 0 };
		ForEach([&result](T value){ result += value; });
		return result;
	}

	template <typename T>
	inline std::size_t Enumerator<T>::Count()
	{
		auto result = 0ull;
		ForEach([&result](T value){ ++result; });
		return result;
	}

	template <typename T>
	inline T Enumerator<T>::Average()
	{
		if (!MoveFirst())
			RaiseEmpty();
		auto count = 1ull;
		auto result = GetCurrent();
		while (MoveNext())
		{
			++count;
			result += GetCurrent();
		}
		return result / static_cast<T>(count);
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::Aggregate(TFunc func)
	{
		if (!MoveFirst())
			RaiseEmpty();
		auto aggregate = GetCurrent();
		while (MoveNext())
			aggregate = func(aggregate, GetCurrent());
		return aggregate;
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::Min(TFunc func)
	{
		return Aggregate([&func](T lhs, T rhs){ return func(lhs, rhs) ? lhs : rhs; });
	}

	template <typename T>
	inline T Enumerator<T>::Min()
	{
		return Min(std::less<T>());
	}

	template <typename T>
	template <typename TFunc>
	inline T Enumerator<T>::Max(TFunc func)
	{
		return Aggregate([&func](T lhs, T rhs){ return func(lhs, rhs) ? rhs : lhs; });
	}

	template <typename T>
	inline T Enumerator<T>::Max()
	{
		return Max(std::less<T>());
	}

	template <typename T>
	inline std::list<typename CoreType<T>::Type> Enumerator<T>::ToList()
	{
		std::list<typename CoreType<T>::Type> result;
		ForEach([&result](T value){ result.push_back(value); });
		return result;
	}

	template <typename T>
	inline std::vector<typename CoreType<T>::Type> Enumerator<T>::ToVector()
	{
		std::vector<typename CoreType<T>::Type> result;
		ForEach([&result](T value){ result.push_back(value); });
		return result;
	}

	template <typename T>
	inline std::set<typename CoreType<T>::Type> Enumerator<T>::ToSet()
	{
		std::set<typename CoreType<T>::Type> result;
		ForEach([&result](T value){ result.insert(value); });
		return result;
	}

	template <typename T>
	inline std::multiset<typename CoreType<T>::Type> Enumerator<T>::ToMultiset()
	{
		std::multiset<typename CoreType<T>::Type> result;
		ForEach([&result](T value){ result.insert(value); });
		return result;
	}

	template <typename T>
	inline std::unordered_set<typename CoreType<T>::Type> Enumerator<T>::ToUnorderedSet()
	{
		std::unordered_set<typename CoreType<T>::Type> result;
		ForEach([&result](T value){ result.insert(value); });
		return result;
	}

	template <typename T>
	inline std::unordered_multiset<typename CoreType<T>::Type> Enumerator<T>::ToUnorderedMultiset()
	{
		std::unordered_multiset<typename CoreType<T>::Type> result;
		ForEach([&result](T value){ result.insert(value); });
		return result;
	}

	template <typename T>
	inline std::deque<typename CoreType<T>::Type> Enumerator<T>::ToDeque()
	{
		std::deque<typename CoreType<T>::Type> result;
		ForEach([&result](T value){ result.push_back(value); });
		return result;
	}

	template <typename T>
	inline std::stack<typename CoreType<T>::Type> Enumerator<T>::ToStack()
	{
		std::stack<typename CoreType<T>::Type> result;
		ForEach([&result](T value){ result.push(value); });
		return result;
	}

	template <typename T>
	inline std::queue<typename CoreType<T>::Type> Enumerator<T>::ToQueue()
	{
		std::queue<typename CoreType<T>::Type> result;
		ForEach([&result](T value){ result.push(value); });
		return result;
	}

	template <typename T>
	inline std::basic_string<typename CoreType<T>::Type> Enumerator<T>::ToString()
	{
		std::basic_string<typename CoreType<T>::Type> result;
		ForEach([&result](T value){ result.push_back(value); });
		return result;
	}

	template <typename T>
	template <typename TFunc>
	inline std::map<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> Enumerator<T>::ToMap(TFunc func)
	{
		std::map<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> result;
		ForEach([&result, &func](T value){ result.insert({ func(value), value }); });
		return result;
	}

	template <typename T>
	template <typename TFunc>
	inline std::multimap<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> Enumerator<T>::ToMultimap(TFunc func)
	{
		std::multimap<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> result;
		ForEach([&result, &func](T value){ result.insert({ func(value), value }); });
		return result;
	}

	template <typename T>
	template <typename TFunc>
	inline std::unordered_map<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> Enumerator<T>::ToUnorderedMap(TFunc func)
	{
		std::unordered_map<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> result;
		ForEach([&result, &func](T value){ result.insert({ func(value), value }); });
		return result;
	}

	template <typename T>
	template <typename TFunc>
	inline std::unordered_multimap<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> Enumerator<T>::ToUnorderedMultimap(TFunc func)
	{
		std::unordered_multimap<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> result;
		ForEach([&result, &func](T value){ result.insert({ func(value), value }); });
		return result;
	}

	template <typename T>
	inline void Enumerator<T>::RaiseEmpty()
	{
		throw std::length_error("sequence contains no elements");
	}

	template <typename T>
	inline void Enumerator<T>::RaiseMultiple()
	{
		throw std::length_error("sequence contains multiple elements");
	}

	template <typename T>
	inline void Enumerator<T>::RaiseIndex()
	{
		throw std::out_of_range("index out of range");
	}
}

