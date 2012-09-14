////////////////////////////////////////////////////////////////////////////////
// Filename:    Enumerator.h
// Description: ...
//
// Created:     2012-09-13 22:29:56
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <functional>
#include <utility>
#include <tuple>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <stdexcept>
#include <iterator>
#include <memory>

namespace Linq
{
	template <typename T> class Enumerator;
	template <typename T, typename TFunc> class WhereEnumerator;
	template <typename T, typename TFunc> class SelectEnumerator;
	template <typename T> class SkipEnumerator;
	template <typename T, typename TFunc> class SkipWhileEnumerator;
	template <typename T> class TakeEnumerator;
	template <typename T, typename TFunc> class TakeWhileEnumerator;
	template <typename T, typename TEnum> class ConcatEnumerator;
	template <typename T, typename TCast> class StaticCastEnumerator;
	template <typename T, typename TFunc> class SelectManyEnumerator;
	template <typename T, typename TSecond, typename TFunc> class ZipEnumerator;
	template <typename T> class IteratorEnumerator;
	template <typename T> class RangeEnumerator;
	template <typename T> class RepeatEnumerator;

	template <typename T>
	class Enumerator
	{
	public:
		typedef Enumerator<T> ThisType;
		typedef T ValueType;
		typedef ThisType InterfaceType;

		virtual bool MoveFirst() = 0;
		virtual bool MoveNext() = 0;
		virtual T GetCurrent() const = 0;

		//ForEach
		template <typename TFunc> TFunc ForEach(TFunc func);

		//Where
		template <typename TFunc> WhereEnumerator<T, TFunc> Where(TFunc func);

		//Single, SingleOrDefault
		T Single();
		template <typename TFunc> T Single(TFunc func);
		T SingleOrDefault();
		T SingleOrDefault(T def);
		template <typename TFunc> T SingleOrDefault(TFunc func);
		template <typename TFunc> T SingleOrDefault(TFunc func, T def);

		//First, FirstOrDefault
		T First();
		template <typename TFunc> T First(TFunc func);
		T FirstOrDefault();
		T FirstOrDefault(T def);
		template <typename TFunc> T FirstOrDefault(TFunc func);
		template <typename TFunc> T FirstOrDefault(TFunc func, T def);

		//Last, LastOrDefault
		T Last();
		template <typename TFunc> T Last(TFunc func);
		T LastOrDefault();
		T LastOrDefault(T def);
		template <typename TFunc> T LastOrDefault(TFunc func);
		template <typename TFunc> T LastOrDefault(TFunc func, T def);

		//ElementAt, ElementAtOrDefault
		T ElementAt(unsigned long position);
		T ElementAtOrDefault(unsigned long position);
		T ElementAtOrDefault(unsigned long position, T def);

		//Select, SelectMany
		template <typename TFunc> SelectEnumerator<T, TFunc> Select(TFunc func);
		template <typename TFunc> SelectManyEnumerator<T, TFunc> SelectMany(TFunc func);

		//Skip, SkipWhile
		SkipEnumerator<T> Skip(unsigned long count);
		template <typename TFunc> SkipWhileEnumerator<T, TFunc> SkipWhile(TFunc func);

		//Take, TakeWhile
		TakeEnumerator<T> Take(unsigned long count);
		template <typename TFunc> TakeWhileEnumerator<T, TFunc> TakeWhile(TFunc func);

		//Concat
		template <typename TEnum> ConcatEnumerator<T, TEnum> Concat(TEnum rhs);

		//Cast<>
		template <typename TCast> StaticCastEnumerator<T, TCast> Cast();

		//Sum, Count, Average, Aggregate, Min, Max
		T Sum();
		unsigned long Count();
		T Average();
		template <typename TFunc> T Aggregate(TFunc func);
		template <typename TFunc> T Min(TFunc func);
		T Min();
		template <typename TFunc> T Max(TFunc func);
		T Max();

		//Zip
		template <typename TSecond> ZipEnumerator<T, TSecond, std::pair<T, TSecond>(T, TSecond)> Zip(Enumerator<TSecond>& second);
		template <typename TSecond, typename TFunc> ZipEnumerator<T, TSecond, TFunc> Zip(Enumerator<TSecond>& second, TFunc transform);

		//ToList, etc...
		std::list<T> ToList();
		std::vector<T> ToVector();
		std::set<T> ToSet();
		std::multiset<T> ToMultiset();
		std::unordered_set<T> ToUnorderedSet();
		std::unordered_multiset<T> ToUnorderedMultiset();
		std::deque<T> ToDeque();
		std::stack<T> ToStack();
		std::queue<T> ToQueue();
		template <typename TFunc> std::map<decltype(std::declval<TFunc>()(std::declval<T>())), T> ToMap(TFunc func);
		template <typename TFunc> std::multimap<decltype(std::declval<TFunc>()(std::declval<T>())), T> ToMultimap(TFunc func);
		template <typename TFunc> std::unordered_map<decltype(std::declval<TFunc>()(std::declval<T>())), T> ToUnorderedMap(TFunc func);
		template <typename TFunc> std::unordered_multimap<decltype(std::declval<TFunc>()(std::declval<T>())), T> ToUnorderedMultimap(TFunc func);

	private:
		static void RaiseEmpty();
		static void RaiseMultiple();
		static void RaiseIndex();
	};

	//From, etc...
	template <typename T> IteratorEnumerator<typename T::iterator> From(T& container);
	template <typename T> IteratorEnumerator<typename T::const_iterator> From(const T& container);
	template <typename T> IteratorEnumerator<typename T::const_iterator> FromConst(const T& container);
	template <typename T> IteratorEnumerator<typename T::reverse_iterator> FromReverse(T& container);
	template <typename T> IteratorEnumerator<typename T::const_reverse_iterator> FromReverse(const T& container);
	template <typename T> IteratorEnumerator<typename T::const_reverse_iterator> FromConstReverse(const T& container);

	//Range
	template <typename T> RangeEnumerator<T> Range(T first, unsigned long count);
	template <typename T> RangeEnumerator<T> Range(T first, unsigned long count, T step);

	//Repeat
	template <typename T> RepeatEnumerator<T> Repeat(T value, unsigned long count);
}

#include "Enumerator.inl"
#include "RepeatEnumerator.inl"
#include "RangeEnumerator.inl"
#include "IteratorEnumerator.inl"
#include "WhereEnumerator.inl"
#include "SelectEnumerator.inl"
#include "SelectManyEnumerator.inl"
#include "SkipEnumerator.inl"
#include "SkipWhileEnumerator.inl"
#include "TakeEnumerator.inl"
#include "TakeWhileEnumerator.inl"
#include "ConcatEnumerator.inl"
#include "StaticCastEnumerator.inl"
#include "ZipEnumerator.inl"

