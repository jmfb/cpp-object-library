////////////////////////////////////////////////////////////////////////////////
// Filename:    Enumerable.Test.cpp
// Description: ...
//
// Created:     2012-09-14 00:49:48
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(EnumeratorTest)
	{
	public:
		EnumeratorTest()
		{
		}

		//Tests the ForEach function for the case when the sequence is empty.
		TEST_METHOD(ForEachEmpty)
		{
			auto called = false;
			Repeat(0, 0).ForEach([&](int value){ called = true; });
			Assert.IsFalse(called);
		}

		//Tests the ForEach function for the case when there are elements in the sequence.
		TEST_METHOD(ForEachValid)
		{
			std::vector<int> results;
			Range(1, 3).ForEach([&](int value){ results.push_back(value); });
			std::vector<int> expected { 1, 2, 3 };
			Assert.AreEqual(expected.size(), results.size(), "size");
			Assert.AreEqual(expected[0], results[0], "[0]");
			Assert.AreEqual(expected[1], results[1], "[1]");
			Assert.AreEqual(expected[2], results[2], "[2]");
		}

		//Tests the ForEach function for the case when a functor is passed and is modified as a result.
		//Verifies the original functor retains its initial value and that the result is another functor with the new value.
		TEST_METHOD(ForEachReturnValue)
		{
			const auto initial = 123;
			const auto expected = initial + 1 + 2 + 3;
			class Functor
			{
			public:
				Functor(int sum)
					: sum(sum)
				{
				}
				void operator()(int value)
				{
					sum += value;
				}
				int sum = 0;
			};
			Functor functor { initial };
			auto result = Range(1, 3).ForEach(functor);
			Assert.IsTrue(typeid(functor) == typeid(result), "type");
			Assert.AreEqual(expected, result.sum, "result.sum");
			Assert.AreEqual(initial, functor.sum, "functor.sum");
		}

		//Tests the Single function for the case when the sequence is empty.
		TEST_METHOD(SingleEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 0).Single();
			}, "sequence contains no elements");
		}

		//Tests the Single function for the case when the sequence contains exactly one element.
		TEST_METHOD(SingleValid)
		{
			const auto value = 123;
			auto result = Repeat(123, 1).Single();
			Assert.AreEqual(value, result);
		}

		//Tests the Single function for the case when the sequence contains multiple elements.
		TEST_METHOD(SingleMultiple)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Range(1, 2).Single();
			}, "sequence contains multiple elements");
		}

		//Tests the Single function that takes a predicate for the case when the sequence is empty.
		TEST_METHOD(SingleWithPredicateEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 5).Single([](int value){ return value > 0; });
			}, "sequence contains no elements");
		}

		//Tests the Single function that takes a predicate for the case when the sequence contains exactly one element.
		TEST_METHOD(SingleWithPredicateValid)
		{
			const auto expected = 3;
			auto result = Range(1, 5).Single([](int value){ return value == expected; });
			Assert.AreEqual(expected, result);
		}

		//Tests the Single function that takes a predicate for the case when the sequence contains multiple elements.
		TEST_METHOD(SingleWithPredicateMultiple)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Range(1, 5).Single([](int value){ return value > 3; });
			}, "sequence contains multiple elements");
		}

		//Tests the SingleOrDefault function for the case when the sequence is empty.
		TEST_METHOD(SingleOrDefaultEmpty)
		{
			const auto expected = int();
			auto result = Repeat(0, 0).SingleOrDefault();
			Assert.AreEqual(expected, result);
		}

		//Tests the SingleOrDefault function for the case when the sequence contains exactly one element.
		TEST_METHOD(SingleOrDefaultValid)
		{
			const auto expected = 123;
			auto result = Repeat(expected, 1).SingleOrDefault();
			Assert.AreEqual(expected, result);
		}

		//Tests the SingleOrDefault function for the case when the sequence contains multiple elements.
		TEST_METHOD(SingleOrDefaultMultiple)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Range(1, 5).SingleOrDefault();
			}, "sequence contains multiple elements");
		}

		//Tests the SingleOrDefault function that specifies the default value for the case when the sequence is empty.
		TEST_METHOD(SingleOrDefaultWithDefaultEmpty)
		{
			const auto expected = 123;
			auto result = Repeat(0, 0).SingleOrDefault(expected);
			Assert.AreEqual(expected, result);
		}

		//Tests the SingleOrDefault function that specifies the default value for the case when the sequence contains exactly one element.
		TEST_METHOD(SingleOrDefaultWithDefaultValid)
		{
			const auto expected = 123;
			auto result = Repeat(expected, 1).SingleOrDefault(0);
			Assert.AreEqual(expected, result);
		}

		//Tests the SingleOrDefault function that specifies the default value for the case when the sequence contains multiple elements.
		TEST_METHOD(SingleOrDefaultWithDefaultMultiple)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Range(1, 5).SingleOrDefault(0);
			}, "sequence contains multiple elements");
		}

		//Tests the SingleOrDefault function that specifies a predicate for the case when the sequence is empty.
		TEST_METHOD(SingleOrDefaultWithPredicateEmpty)
		{
			const auto expected = int();
			auto result = Repeat(0, 5).SingleOrDefault([](int value){ return value > 0; });
			Assert.AreEqual(expected, result);
		}

		//Tests the SingleOrDefault function that specifies a predicate for the case when the sequence contains exactly one element.
		TEST_METHOD(SingleOrDefaultWithPredicateValid)
		{
			const auto expected = 3;
			auto result = Range(1, 5).SingleOrDefault([](int value){ return value == expected; });
			Assert.AreEqual(expected, result);
		}

		//Tests the SingleOrDefault function that specifies a predicate for the case when the sequence contains multiple elements.
		TEST_METHOD(SingleOrDefaultWithPredicateMultiple)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Range(1, 5).SingleOrDefault([](int value){ return value > 3; });
			}, "sequence contains multiple elements");
		}

		//Tests the SingleOrDefault function that specifies both a predicate and the default value for the case when the sequence is empty.
		TEST_METHOD(SingleOrDefaultWithPredicateAndDefaultEmpty)
		{
			const auto expected = 123;
			auto result = Repeat(0, 5).SingleOrDefault([](int value){ return value > 0; }, expected);
			Assert.AreEqual(expected, result);
		}

		//Tests the SingleOrDefault function that specifies both a predicate and the default value for the case when the sequence contains exactly one element.
		TEST_METHOD(SingleOrDefaultWithPredicateAndDefaultValid)
		{
			const auto expected = 3;
			auto result = Range(1, 5).SingleOrDefault([](int value){ return value == expected; }, 0);
			Assert.AreEqual(expected, result);
		}

		//Tests the SingleOrDefault function that specifies both a predicate and the default value for the case when the sequence contains multiple elements.
		TEST_METHOD(SingleOrDefaultWithPredicateAndDefaultMultiple)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Range(1, 5).SingleOrDefault([](int value){ return value > 3; }, 0);
			}, "sequence contains multiple elements");
		}

		//Tests the First function for the case when the sequence is empty.
		TEST_METHOD(FirstEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 0).First();
			}, "sequence contains no elements");
		}

		//Tests the First function for the case when the sequence is not empty.
		TEST_METHOD(FirstValid)
		{
			const auto expected = 123;
			auto result = Range(expected, 5).First();
			Assert.AreEqual(expected, result);
		}

		//Tests the First function that specifies a predicate for the case when the sequence is empty.
		TEST_METHOD(FirstWithPredicateEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Linq::Repeat(0, 5).First([](int value){ return value > 0; });
			}, "sequence contains no elements");
		}

		//Tests the First function that specifies a predicate for the case when the sequence is not empty.
		TEST_METHOD(FirstWithPredicateValid)
		{
			const auto expected = 3;
			auto result = Range(1, 5).First([](int value){ return value > 2; });
			Assert.AreEqual(expected, result);
		}

		//Tests the FirstOrDefault function for the case when the sequence is empty.
		TEST_METHOD(FirstOrDefaultEmpty)
		{
			const auto expected = int();
			auto result = Repeat(0, 0).FirstOrDefault();
			Assert.AreEqual(expected, result);
		}

		//Tests the FirstOrDefault function for the case when the sequence is not empty.
		TEST_METHOD(FirstOrDefaultValid)
		{
			const auto expected = 123;
			auto result = Range(expected, 5).FirstOrDefault();
			Assert.AreEqual(expected, result);
		}

		//Tests the FirstOrDefault function that specifies a default value for the case when the sequence is empty.
		TEST_METHOD(FirstOrDefaultWithDefaultEmpty)
		{
			const auto expected = 123;
			auto result = Repeat(0, 0).FirstOrDefault(expected);
			Assert.AreEqual(expected, result);
		}

		//Tests the FirstOrDefault function that specifies a default value for the case when the sequence is not empty.
		TEST_METHOD(FirstOrDefaultWithDefaultValid)
		{
			const auto expected = 123;
			auto result = Range(expected, 5).FirstOrDefault(0);
			Assert.AreEqual(expected, result);
		}

		//Tests the FirstOrDefault function that specifies a predicate for the case when the sequence is empty.
		TEST_METHOD(FirstOrDefaultWithPredicateEmpty)
		{
			const auto expected = int();
			auto result = Repeat(0, 5).FirstOrDefault([](int value){ return value > 0; });
			Assert.AreEqual(expected, result);
		}

		//Tests the FirstOrDefault function that specifies a predicate for the case when the sequence is not empty.
		TEST_METHOD(FirstOrDefaultWithPredicateValid)
		{
			const auto expected = 3;
			auto result = Range(1, 5).FirstOrDefault([](int value){ return value > 2; });
			Assert.AreEqual(expected, result);
		}

		//Tests the FirstOrDefault function that specifies both a predicate and a default value for the case when the sequence is empty.
		TEST_METHOD(FirstOrDefaultWithPredicateAndDefaultEmpty)
		{
			const auto expected = 123;
			auto result = Repeat(0, 5).FirstOrDefault([](int value){ return value > 0; }, expected);
			Assert.AreEqual(expected, result);
		}

		//Tests the FirstOrDefault function that specifies both a predicate and a default value for the case when the sequence is not empty.
		TEST_METHOD(FirstOrDefaultWithPredicateAndDefaultValid)
		{
			const auto expected = 3;
			auto result = Range(1, 5).FirstOrDefault([](int value){ return value > 2; }, 0);
			Assert.AreEqual(expected, result);
		}

		//Tests the Last function for the case when the sequence is empty.
		TEST_METHOD(LastEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 0).Last();
			}, "sequence contains no elements");
		}

		//Tests the Last function for the case when the sequence is not empty.
		TEST_METHOD(LastValid)
		{
			const auto expected = 5;
			auto result = Range(1, expected).Last();
			Assert.AreEqual(expected, result);
		}

		//Tests the Last function that specifies a predicate for the case when the sequence is empty.
		TEST_METHOD(LastWithPredicateEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 5).Last([](int value){ return value > 0; });
			}, "sequence contains no elements");
		}

		//Tests the Last function that specifies a predicate for the case when the sequence is not empty.
		TEST_METHOD(LastWithPredicateValid)
		{
			const auto expected = 3;
			auto result = Range(1, 5).Last([](int value){ return value < 4; });
			Assert.AreEqual(expected, result);
		}

		//Tests the LastOrDefault function for the case when the sequence is empty.
		TEST_METHOD(LastOrDefaultEmpty)
		{
			const auto expected = int();
			auto result = Repeat(0, 0).LastOrDefault();
			Assert.AreEqual(expected, result);
		}

		//Tests the LastOrDefault function for the case when the sequence is not empty.
		TEST_METHOD(LastOrDefaultValid)
		{
			const auto expected = 5;
			auto result = Range(1, expected).LastOrDefault();
			Assert.AreEqual(expected, result);
		}

		//Tests the LastOrDefault function that specifies a default value for the case when the sequence is empty.
		TEST_METHOD(LastOrDefaultWithDefaultEmpty)
		{
			const auto expected = 123;
			auto result = Repeat(0, 0).LastOrDefault(expected);
			Assert.AreEqual(expected, result);
		}

		//Tests the LastOrDefault function that specifies a default value for the case when the sequence is not empty.
		TEST_METHOD(LastOrDefaultWithDefaultValid)
		{
			const auto expected = 5;
			auto result = Range(1, expected).LastOrDefault(0);
			Assert.AreEqual(expected, result);
		}

		//Tests the LastOrDefault function that specifies a predicate for the case when the sequence is empty.
		TEST_METHOD(LastOrDefaultWithPredicateEmpty)
		{
			const auto expected = int();
			auto result = Repeat(0, 5).LastOrDefault([](int value){ return value > 0; });
			Assert.AreEqual(expected, result);
		}

		//Tests the LastOrDefault function that specifies a predicate for the case when the sequence is not empty.
		TEST_METHOD(LastOrDefaultWithPredicateValid)
		{
			const auto expected = 3;
			auto result = Range(1, 5).LastOrDefault([](int value){ return value < 4; });
			Assert.AreEqual(expected, result);
		}

		//Tests the LastOrDefault function that specifies both a predicate and a default value for the case when the sequence is empty.
		TEST_METHOD(LastOrDefaultWithPredicateAndDefaultEmpty)
		{
			const auto expected = 123;
			auto result = Repeat(0, 5).LastOrDefault([](int value){ return value > 0; }, expected);
			Assert.AreEqual(expected, result);
		}

		//Tests the LastOrDefault function that specifies both a predicate and a default value for the case when the sequence is not empty.
		TEST_METHOD(LastOrdefaultWithPredicateAndDefaultEmpty)
		{
			const auto expected = 3;
			auto result = Range(1, 5).LastOrDefault([](int value){ return value < 4; }, 0);
			Assert.AreEqual(expected, result);
		}

		//Tests the ElementAt function for the case when valid.
		TEST_METHOD(ElementAtValid)
		{
			auto result = Range(1, 5).ElementAt(2);
			Assert.AreEqual(3, result);
		}

		//Tests the ElementAt function for the case when the sequence is too short.
		TEST_METHOD(ElementAtInvalid)
		{
			Assert.ThrowsType<std::out_of_range>([]()
			{
				Range(1, 5).ElementAt(5);
			}, "index out of range");
		}

		//Tests the ElementAtOrDefault function for the case when valid.
		TEST_METHOD(ElementAtOrDefaultValid)
		{
			auto result = Range(1, 5).ElementAtOrDefault(2);
			Assert.AreEqual(3, result);
		}

		//Tests the ElementAtOrDefault function for the case when the sequence is too short.
		TEST_METHOD(ElementAtOrDefaultInvalid)
		{
			const auto expected = int();
			auto result = Range(1, 5).ElementAtOrDefault(5);
			Assert.AreEqual(expected, result);
		}

		//Tests the ElementAtOrDefault function that specifies the default value for the case when valid.
		TEST_METHOD(ElementAtOrDefaultWithDefaultValid)
		{
			auto result = Range(1, 5).ElementAtOrDefault(2, 0);
			Assert.AreEqual(3, result);
		}

		//Tests the ElementAtOrDefault function that specifies the default value for the case when the sequence is too short.
		TEST_METHOD(ElementAtOrDefaultWithDefaultInvalid)
		{
			const auto expected = 123;
			auto result = Range(1, 5).ElementAtOrDefault(5, expected);
			Assert.AreEqual(expected, result);
		}

		//Tests the Sum function for the case when the sequence is empty.
		TEST_METHOD(SumEmpty)
		{
			auto result = Repeat(0, 0).Sum();
			Assert.AreEqual(0, result);
		}

		//Tests the Sum function for the case when valid.
		TEST_METHOD(SumValid)
		{
			const auto expected = 1 + 2 + 3 + 4 + 5;
			auto result = Range(1, 5).Sum();
			Assert.AreEqual(expected, result);
		}

		//Tests the Count function for the case when the sequence is empty.
		TEST_METHOD(CountEmpty)
		{
			auto result = Repeat(0, 0).Count();
			Assert.AreEqual(0ull, result);
		}

		//Tests the Count function for the case when valid.
		TEST_METHOD(CountValid)
		{
			const auto expected = 5ull;
			auto result = Repeat(1, expected).Count();
			Assert.AreEqual(expected, result);
		}

		//Tests the Average function for the case when the sequence is empty.
		TEST_METHOD(AverageEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 0).Average();
			}, "sequence contains no elements");
		}

		//Tests the Average function for the case when valid.
		TEST_METHOD(AverageValid)
		{
			const auto expected = (1 + 2 + 3 + 4 + 5) / 5;
			auto result = Range(1, 5).Average();
			Assert.AreEqual(expected, result);
		}

		//Tests the Aggregate function for the case when the sequence is empty.
		TEST_METHOD(AggregateEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 0).Aggregate([](int x, int y){ return 0; });
			}, "sequence contains no elements");
		}

		//Tests the Aggregate function for the case when valid.
		TEST_METHOD(AggregateValid)
		{
			const auto expected = 1 * 2 * 3 * 4 * 5;
			auto result = Range(1, 5).Aggregate([](int current, int next){ return current * next; });
			Assert.AreEqual(expected, result);
		}

		//Tests the Min function for the case when the sequence is empty.
		TEST_METHOD(MinEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 0).Min();
			}, "sequence contains no elements");
		}

		//Tests the Min function for the case when valid.
		TEST_METHOD(MinValid)
		{
			auto result = Range(5, 5, -1).Min();
			Assert.AreEqual(1, result);
		}

		//Tests the Min function that specifies a predicate for the case when the sequence is empty.
		TEST_METHOD(MinWithPredicateEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 0).Min([](int x, int y){ return x < y; });
			}, "sequence contains no elements");
		}

		//Tests the Min function that specifies a predicate for the case when valid.
		TEST_METHOD(MinWithPredicateValid)
		{
			auto result = Range(5, 5, -1).Min([](int x, int y){ return x < y; });
			Assert.AreEqual(1, result);
		}

		//Tests the Max function for the case when the sequence is empty.
		TEST_METHOD(MaxEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 0).Max();
			}, "sequence contains no elements");
		}

		//Tests the Max function for the case when valid.
		TEST_METHOD(MaxValid)
		{
			const auto expected = 5;
			auto result = Range(1, expected).Max();
			Assert.AreEqual(expected, result);
		}

		//Tests the Max function that specifies a predicate for the case when the sequence is empty.
		TEST_METHOD(MaxWithPredicateEmpty)
		{
			Assert.ThrowsType<std::length_error>([]()
			{
				Repeat(0, 0).Max([](int x, int y){ return x < y; });
			}, "sequence contains no elements");
		}

		//Tests the Max function that specifies a predicate for the case when valid.
		TEST_METHOD(MaxWithPredicateValid)
		{
			const auto expected = 5;
			auto result = Range(1, expected).Max([](int x, int y){ return x < y; });
			Assert.AreEqual(expected, result);
		}

		//Tests the ToList function for the case when valid.
		TEST_METHOD(ToListValid)
		{
			const std::size_t size = 3;
			auto result = Range(1, size).ToList();
			Assert.IsTrue(typeid(result) == typeid(std::list<int>), "type");
			Assert.AreEqual(size, result.size(), "size");
			auto iter = result.begin();
			Assert.AreEqual(1, *iter++, "[0]");
			Assert.AreEqual(2, *iter++, "[1]");
			Assert.AreEqual(3, *iter++, "[2]");
		}

		//Tests the ToVector function for the case when valid.
		TEST_METHOD(ToVectorValid)
		{
			const std::size_t size = 3;
			auto result = Range(1, size).ToVector();
			Assert.IsTrue(typeid(result) == typeid(std::vector<int>), "type");
			Assert.AreEqual(size, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(2, result[1], "[1]");
			Assert.AreEqual(3, result[2], "[2]");
		}

		//Tests the ToSet function for the case when valid.
		TEST_METHOD(ToSetValid)
		{
			auto result = From(std::vector<int>{ 4, 1, 1, 7, 4 }).ToSet();
			Assert.IsTrue(typeid(result) == typeid(std::set<int>), "type");
			Assert.AreEqual(3ull, result.size(), "size");
			auto iter = result.begin();
			Assert.AreEqual(1, *iter++, "[0]");
			Assert.AreEqual(4, *iter++, "[1]");
			Assert.AreEqual(7, *iter++, "[2]");
		}

		//Tests the ToMultiset function for the case when valid.
		TEST_METHOD(ToMultisetValid)
		{
			auto result = From(std::vector<int>{ 4, 1, 1, 7, 4 }).ToMultiset();
			Assert.IsTrue(typeid(result) == typeid(std::multiset<int>), "type");
			Assert.AreEqual(5ull, result.size(), "size");
			auto iter = result.begin();
			Assert.AreEqual(1, *iter++, "[0]");
			Assert.AreEqual(1, *iter++, "[1]");
			Assert.AreEqual(4, *iter++, "[2]");
			Assert.AreEqual(4, *iter++, "[3]");
			Assert.AreEqual(7, *iter++, "[4]");
		}

		//Tests the ToUnorderedSet function for the case when valid.
		TEST_METHOD(ToUnorderedSetValid)
		{
			auto result = From(std::vector<int>{ 4, 1, 1, 7, 4}).ToUnorderedSet();
			Assert.IsTrue(typeid(result) == typeid(std::unordered_set<int>), "type");
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.IsTrue(result.find(1) != result.end(), "1");
			Assert.IsTrue(result.find(4) != result.end(), "4");
			Assert.IsTrue(result.find(7) != result.end(), "7");
		}

		//Tests the ToUnorderedMultiset function for the case when valid.
		TEST_METHOD(ToUnorderedMultisetValid)
		{
			auto result = From(std::vector<int>{ 4, 1, 1, 7, 4 }).ToUnorderedMultiset();
			Assert.IsTrue(typeid(result) == typeid(std::unordered_multiset<int>), "type");
			Assert.AreEqual(5ull, result.size(), "size");
			auto iter1 = result.equal_range(1);
			Assert.AreEqual(2, std::distance(iter1.first, iter1.second), "1");
			auto iter4 = result.equal_range(4);
			Assert.AreEqual(2, std::distance(iter4.first, iter4.second), "4");
			auto iter7 = result.equal_range(7);
			Assert.AreEqual(1, std::distance(iter7.first, iter7.second), "7");
		}

		//Tests the ToDeque function for the case when valid.
		TEST_METHOD(ToDequeValid)
		{
			const std::size_t size = 3;
			auto result = Range(1, size).ToDeque();
			Assert.IsTrue(typeid(result) == typeid(std::deque<int>), "type");
			Assert.AreEqual(size, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(2, result[1], "[1]");
			Assert.AreEqual(3, result[2], "[2]");
		}

		//Tests the ToStack function for the case when valid.
		TEST_METHOD(ToStackValid)
		{
			const std::size_t size = 3;
			auto result = Range(1, size).ToStack();
			Assert.IsTrue(typeid(result) == typeid(std::stack<int>), "type");
			Assert.AreEqual(size, result.size(), "size");
			Assert.AreEqual(3, result.top(), "[0]");
			result.pop();
			Assert.AreEqual(2, result.top(), "[1]");
			result.pop();
			Assert.AreEqual(1, result.top(), "[2]");
		}

		//Tests the ToQueue function for the case when valid.
		TEST_METHOD(ToQueueValid)
		{
			const std::size_t size = 3;
			auto result = Range(1, size).ToQueue();
			Assert.IsTrue(typeid(result) == typeid(std::queue<int>), "type");
			Assert.AreEqual(size, result.size(), "size");
			Assert.AreEqual(1, result.front(), "[0]");
			result.pop();
			Assert.AreEqual(2, result.front(), "[1]");
			result.pop();
			Assert.AreEqual(3, result.front(), "[2]");
		}

		//Tests the ToString function for the cas when valid.
		TEST_METHOD(ToStringValid)
		{
			auto result = From(std::string{ "hello world" }).Select([](char ch) -> char { return std::toupper(ch); }).ToString();
			Assert.AreEqual("HELLO WORLD", result);
		}

		//Tests the ToMap function for the case when valid.
		TEST_METHOD(ToMapValid)
		{
			auto result = From(std::vector<int>{ 4, 1, 1, 7, 4 }).ToMap([](int value){ return value * 2; });
			Assert.IsTrue(typeid(result) == typeid(std::map<int, int>), "type");
			Assert.AreEqual(3ull, result.size(), "size");
			auto iter = result.begin();
			Assert.AreEqual(2, iter->first, "[0].key");
			Assert.AreEqual(1, iter->second, "[0].value");
			++iter;
			Assert.AreEqual(8, iter->first, "[1].key");
			Assert.AreEqual(4, iter->second, "[1].value");
			++iter;
			Assert.AreEqual(14, iter->first, "[2].key");
			Assert.AreEqual(7, iter->second, "[2].value");
		}

		//Tests the ToMultimap function for the case when valid.
		TEST_METHOD(ToMultimapValid)
		{
			auto result = From(std::vector<int>{ 4, 1, 1, 7, 4 }).ToMultimap([](int value){ return value * 2; });
			Assert.IsTrue(typeid(result) == typeid(std::multimap<int, int>), "type");
			Assert.AreEqual(5ull, result.size(), "size");
			auto iter = result.begin();
			Assert.AreEqual(2, iter->first, "[0].key");
			Assert.AreEqual(1, iter->second, "[0].value");
			++iter;
			Assert.AreEqual(2, iter->first, "[1].key");
			Assert.AreEqual(1, iter->second, "[1].value");
			++iter;
			Assert.AreEqual(8, iter->first, "[2].key");
			Assert.AreEqual(4, iter->second, "[2].value");
			++iter;
			Assert.AreEqual(8, iter->first, "[3].key");
			Assert.AreEqual(4, iter->second, "[3].value");
			++iter;
			Assert.AreEqual(14, iter->first, "[4].key");
			Assert.AreEqual(7, iter->second, "[4].value");
		}

		//Tests the ToUnorderedMap function for the case when valid.
		TEST_METHOD(ToUnorderedMapValid)
		{
			auto result = From(std::vector<int>{ 4, 1, 1, 7, 4 }).ToUnorderedMap([](int value){ return value * 2; });
			Assert.IsTrue(typeid(result) == typeid(std::unordered_map<int, int>), "type");
			Assert.AreEqual(3ull, result.size(), "size");
			auto iter1 = result.find(2);
			Assert.IsTrue(iter1 != result.end(), "[0]");
			Assert.AreEqual(1, iter1->second, "[0].value");
			auto iter4 = result.find(8);
			Assert.IsTrue(iter4 != result.end(), "[1]");
			Assert.AreEqual(4, iter4->second, "[1].value");
			auto iter7 = result.find(14);
			Assert.IsTrue(iter7 != result.end(), "[2]");
			Assert.AreEqual(7, iter7->second, "[2].value");
		}

		//Tests the ToUnorderedMultimap function for the case when valid.
		TEST_METHOD(ToUnorderedMultimapValid)
		{
			auto result = From(std::vector<int>{ 4, 1, 1, 7, 4 }).ToUnorderedMultimap([](int value){ return value * 2; });
			Assert.IsTrue(typeid(result) == typeid(std::unordered_multimap<int, int>), "type");
			Assert.AreEqual(5ull, result.size(), "size");
			auto iter1 = result.equal_range(2);
			Assert.AreEqual(2, std::distance(iter1.first, iter1.second), "[0]");
			Assert.AreEqual(1, iter1.first->second, "[0].value(0)");
			++iter1.first;
			Assert.AreEqual(1, iter1.first->second, "[0].value(1)");
			auto iter4 = result.equal_range(8);
			Assert.AreEqual(2, std::distance(iter4.first, iter4.second), "[1]");
			Assert.AreEqual(4, iter4.first->second, "[1].value(0)");
			++iter4.first;
			Assert.AreEqual(4, iter4.first->second, "[1].value(1)");
			auto iter7 = result.equal_range(14);
			Assert.AreEqual(1, std::distance(iter7.first, iter7.second), "[2]");
			Assert.AreEqual(7, iter7.first->second, "[2].value");
		}
	};
}

