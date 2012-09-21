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
#include <string>

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
	template <typename T, template <typename> class TEnumerator, typename TSecond, typename TFunc> class ZipEnumerator;
	template <typename T> class IteratorEnumerator;
	template <typename T> class RangeEnumerator;
	template <typename T> class RepeatEnumerator;
	template <typename T, typename TKey, typename TIter> class GroupEnumerator;
	template <typename T, typename TFunc> class GroupByEnumerator;

	template <typename T>
	class CoreType
	{
	public:
		typedef typename std::remove_const<typename std::remove_reference<T>::type>::type Type;
	};

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
		T ElementAt(std::size_t position);
		T ElementAtOrDefault(std::size_t position);
		T ElementAtOrDefault(std::size_t position, T def);

		//Select, SelectMany
		template <typename TFunc> SelectEnumerator<T, TFunc> Select(TFunc func);
		template <typename TFunc> SelectManyEnumerator<T, TFunc> SelectMany(TFunc func);

		//Skip, SkipWhile
		SkipEnumerator<T> Skip(std::size_t count);
		template <typename TFunc> SkipWhileEnumerator<T, TFunc> SkipWhile(TFunc func);

		//Take, TakeWhile
		TakeEnumerator<T> Take(std::size_t count);
		template <typename TFunc> TakeWhileEnumerator<T, TFunc> TakeWhile(TFunc func);

		//Concat
		template <typename TEnum> ConcatEnumerator<T, TEnum> Concat(TEnum rhs);

		//Cast<>
		template <typename TCast> StaticCastEnumerator<T, TCast> Cast();

		//Sum, Count, Average, Aggregate, Min, Max
		T Sum();
		std::size_t Count();
		T Average();
		template <typename TFunc> T Aggregate(TFunc func);
		template <typename TFunc> T Min(TFunc func);
		T Min();
		template <typename TFunc> T Max(TFunc func);
		T Max();

		//Zip
		template <template <typename> class TEnumerator, typename TSecond>
		ZipEnumerator<T, TEnumerator, TSecond, std::function<std::pair<T, TSecond>(T, TSecond)>> Zip(TEnumerator<TSecond> second);
		template <template <typename> class TEnumerator, typename TSecond, typename TFunc>
		ZipEnumerator<T, TEnumerator, TSecond, TFunc> Zip(TEnumerator<TSecond> second, TFunc transform);

		//GroupBy
		template <typename TFunc>
		GroupByEnumerator<T, TFunc> GroupBy(TFunc func);

		//ToList, etc...
		std::list<typename CoreType<T>::Type> ToList();
		std::vector<typename CoreType<T>::Type> ToVector();
		std::set<typename CoreType<T>::Type> ToSet();
		std::multiset<typename CoreType<T>::Type> ToMultiset();
		std::unordered_set<typename CoreType<T>::Type> ToUnorderedSet();
		std::unordered_multiset<typename CoreType<T>::Type> ToUnorderedMultiset();
		std::deque<typename CoreType<T>::Type> ToDeque();
		std::stack<typename CoreType<T>::Type> ToStack();
		std::queue<typename CoreType<T>::Type> ToQueue();
		std::basic_string<typename CoreType<T>::Type> ToString();

		template <typename TFunc>
		std::map<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> ToMap(TFunc func);

		template <typename TFunc>
		std::multimap<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> ToMultimap(TFunc func);

		template <typename TFunc>
		std::unordered_map<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> ToUnorderedMap(TFunc func);

		template <typename TFunc>
		std::unordered_multimap<decltype(std::declval<TFunc>()(std::declval<T>())), typename CoreType<T>::Type> ToUnorderedMultimap(TFunc func);

	private:
		static void RaiseEmpty() __attribute__((noreturn));
		static void RaiseMultiple() __attribute__((noreturn));
		static void RaiseIndex() __attribute__((noreturn));
	};

	//From, etc...
	template <typename T> IteratorEnumerator<T> From(T first, T last);
	template <typename T> IteratorEnumerator<typename T::iterator> From(T& container);
	template <typename T> IteratorEnumerator<typename T::const_iterator> From(const T& container);
	template <typename T> IteratorEnumerator<typename T::const_iterator> FromConst(const T& container);
	template <typename T> IteratorEnumerator<typename T::reverse_iterator> FromReverse(T& container);
	template <typename T> IteratorEnumerator<typename T::const_reverse_iterator> FromReverse(const T& container);
	template <typename T> IteratorEnumerator<typename T::const_reverse_iterator> FromConstReverse(const T& container);

	//Range
	template <typename T> RangeEnumerator<T> Range(T first, std::size_t count);
	template <typename T> RangeEnumerator<T> Range(T first, std::size_t count, T step);

	//Repeat
	template <typename T> RepeatEnumerator<T> Repeat(T value, std::size_t count);
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
#include "GroupEnumerator.inl"
#include "GroupByEnumerator.inl"

