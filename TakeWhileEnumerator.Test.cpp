////////////////////////////////////////////////////////////////////////////////
// Filename:    TakeWhileEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:32
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(TakeWhileEnumeratorTest)
	{
	public:
		TakeWhileEnumeratorTest()
		{
		}

		//Tests the TakeWhile function for the case when taking nothing.
		TEST_METHOD(TakeWhileNone)
		{
			auto result = Range(1, 5).TakeWhile([](int){ return false; }).ToVector();
			Assert.IsTrue(result.empty());
		}

		//Tests the TakeWhile function for the case when taking some items from a sequence.
		TEST_METHOD(TakeWhileSome)
		{
			auto result = Range(1, 5).Concat(Range(1, 5)).TakeWhile([](int value){ return value < 4; }).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(2, result[1], "[1]");
			Assert.AreEqual(3, result[2], "[2]");
		}

		//Tests the TakeWhile function for the case when taking all items from a sequence.
		TEST_METHOD(TakeWhileAll)
		{
			auto result = Range(1, 3).TakeWhile([](int){ return true; }).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(2, result[1], "[1]");
			Assert.AreEqual(3, result[2], "[2]");
		}
	};
}

