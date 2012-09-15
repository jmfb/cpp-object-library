////////////////////////////////////////////////////////////////////////////////
// Filename:    RepeatEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:02
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(RepeatEnumeratorTest)
	{
	public:
		RepeatEnumeratorTest()
		{
		}

		TEST_METHOD(RepeatValid)
		{
			const auto expected = 123;
			const std::size_t count = 100;
			std::size_t result = 0;
			Repeat(expected, count).ForEach([&result](int value)
			{
				Assert.AreEqual(expected, value, "value");
				++result;
			});
			Assert.AreEqual(count, result, "count");
		}
	};
}

