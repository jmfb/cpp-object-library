////////////////////////////////////////////////////////////////////////////////
// Filename:    ConcatEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:35
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(ConcatEnumeratorTest)
	{
	public:
		ConcatEnumeratorTest()
		{
		}

		//Tests the Concat function for the case when the first sequence is empty.
		TEST_METHOD(ConcatFirstEmpty)
		{
			auto result = Repeat(0, 0).Concat(Range(1, 3)).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(2, result[1], "[1]");
			Assert.AreEqual(3, result[2], "[2]");
		}

		//Tests the Concat function for the case when the second sequence is empty.
		TEST_METHOD(ConcatSecondEmpty)
		{
			auto result = Range(1, 3).Concat(Repeat(0, 0)).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(2, result[1], "[1]");
			Assert.AreEqual(3, result[2], "[2]");
		}

		//Tests the Concat function for the case when both sequences are empty.
		TEST_METHOD(ConcatBothEmpty)
		{
			auto result = Repeat(0, 0).Concat(Repeat(0, 0)).ToVector();
			Assert.IsTrue(result.empty());
		}

		//Tests the Concat function for the case when both sequences are not empty.
		TEST_METHOD(ConcatValid)
		{
			auto result = Range(1, 2).Concat(Range(3, 2)).ToVector();
			Assert.AreEqual(4ull, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(2, result[1], "[1]");
			Assert.AreEqual(3, result[2], "[2]");
			Assert.AreEqual(4, result[3], "[3]");
		}
	};
}

