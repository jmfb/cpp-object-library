////////////////////////////////////////////////////////////////////////////////
// Filename:    TakeEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:29
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(TakeEnumeratorTest)
	{
	public:
		TakeEnumeratorTest()
		{
		}

		//Tests the Take function for the case when not taking anything.
		TEST_METHOD(TakeNone)
		{
			auto result = Range(1, 5).Take(0).ToVector();
			Assert.IsTrue(result.empty());
		}

		//Tests the Take function for the case when taking some items from a sequence.
		TEST_METHOD(TakeValid)
		{
			auto result = Range(1, 5).Take(3).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(2, result[1], "[1]");
			Assert.AreEqual(3, result[2], "[2]");
		}

		//Tests the Take function for the case when taking more than a sequence contains.
		TEST_METHOD(TakeAll)
		{
			auto result = Range(1, 3).Take(4).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(2, result[1], "[1]");
			Assert.AreEqual(3, result[2], "[2]");
		}
	};
}

