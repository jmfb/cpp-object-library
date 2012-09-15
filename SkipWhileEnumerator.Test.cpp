////////////////////////////////////////////////////////////////////////////////
// Filename:    SkipWhileEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:25
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(SkipWhileEnumeratorTest)
	{
	public:
		SkipWhileEnumeratorTest()
		{
		}

		//Tests the SkipWhile function for the case when skipping nothing.
		TEST_METHOD(SkipWhileNone)
		{
			auto result = Range(1, 3).SkipWhile([](int){ return false; }).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(2, result[1], "[1]");
			Assert.AreEqual(3, result[2], "[2]");
		}

		//Tests the SkipWhile function for the normal case when some items are skipped.
		TEST_METHOD(SkipWhileValid)
		{
			auto result = Range(1, 4).SkipWhile([](int value){ return value % 2 == 1; }).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(2, result[0], "[0]");
			Assert.AreEqual(3, result[1], "[1]");
			Assert.AreEqual(4, result[2], "[2]");
		}

		//Tests the SkipWhile function for the case when the entire sequence is skipped.
		TEST_METHOD(SkipWhileAll)
		{
			auto result = Range(1, 5).SkipWhile([](int){ return true; }).ToVector();
			Assert.IsTrue(result.empty());
		}
	};
}

