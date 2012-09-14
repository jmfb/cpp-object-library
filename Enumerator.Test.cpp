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
			Linq::Repeat(0, 0).ForEach([&](int value){ called = true; });
			Assert.IsFalse(called);
		}

		//Tests the ForEach function for the case when there are elements in the sequence.	
		TEST_METHOD(ForEachValid)
		{
			std::vector<int> results;
			Linq::Range(1, 3).ForEach([&](int value){ results.push_back(value); });
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
			constexpr auto initial = 123;
			constexpr auto expected = initial + 1 + 2 + 3;
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
			auto result = Linq::Range(1, 3).ForEach(functor);
			Assert.IsTrue(typeid(functor) == typeid(result), "type");
			Assert.AreEqual(expected, result.sum, "result.sum");
			Assert.AreEqual(initial, functor.sum, "functor.sum");
		}

		//Tests the Single function for the case when the sequence is empty.
		TEST_METHOD(SingleEmpty)
		{
			Assert.ThrowsType<std::length_error>([](){ Linq::Repeat(0, 0).Single(); }, "sequence contains no elements");
		}

		//Tests the Single function for the case when the sequence contains exactly one element.
		TEST_METHOD(SingleValid)
		{
			constexpr auto value = 123;
			auto result = Linq::Repeat(123, 1).Single();
			Assert.AreEqual(value, result);
		}

		//Tests the Single function for the case when the sequence contains multiple elements.
		TEST_METHOD(SingleMultiple)
		{
			Assert.ThrowsType<std::length_error>([](){ Linq::Range(1, 2).Single(); }, "sequence contains multiple elements");
		}

		//TODO: left off here
	};
}

