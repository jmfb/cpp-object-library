////////////////////////////////////////////////////////////////////////////////
// Filename:    RangeEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:05
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(RangeEnumeratorTest)
	{
	public:
		RangeEnumeratorTest()
		{
		}

		TEST_METHOD(RangeValid)
		{
			const auto initial = 123;
			const std::size_t count = 100;
			std::size_t result = 0;
			auto next = initial;
			Range(initial, count).ForEach([&result, &next](int value)
			{
				Assert.AreEqual(next, value, "value");
				++next;
				++result;
			});
			Assert.AreEqual(count, result, "count");
		}

		TEST_METHOD(RangeStepValid)
		{
			const auto initial = 123;
			const std::size_t count = 100;
			const auto step = 69;
			auto next = initial;
			std::size_t result = 0;
			Range(initial, count, step).ForEach([&result, &next](int value)
			{
				Assert.AreEqual(next, value, "value");
				next += step;
				++result;
			});
			Assert.AreEqual(count, result, "count");
		}
	};
}

