////////////////////////////////////////////////////////////////////////////////
// Filename:    ZipEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:41
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(ZipEnumeratorTest)
	{
	public:
		ZipEnumeratorTest()
		{
		}

		//Tests the Zip function for the case when the first sequence is empty.
		TEST_METHOD(ZipFirstEmpty)
		{
			auto result = Repeat(0, 0).Zip(Range(1, 3)).ToVector();
			Assert.IsTrue(result.empty());
		}

		//Tests the Zip function for the case when the second sequence is empty.
		TEST_METHOD(ZipSecondEmpty)
		{
			auto result = Range(1, 3).Zip(Repeat(0, 0)).ToVector();
			Assert.IsTrue(result.empty());
		}

		//Tests the Zip function for the case when both sequences are empty.
		TEST_METHOD(ZipBothEmpty)
		{
			auto result = Repeat(0, 0).Zip(Repeat(0, 0)).ToVector();
			Assert.IsTrue(result.empty());
		}

		//Tests the Zip function for the case when the first sequence is shorter.
		TEST_METHOD(ZipFirstShorter)
		{
			auto result = Range(1, 3).Zip(Range(5, 5, -1)).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1, result[0].first, "[0].first");
			Assert.AreEqual(5, result[0].second, "[0].second");
			Assert.AreEqual(2, result[1].first, "[1].first");
			Assert.AreEqual(4, result[1].second, "[1].second");
			Assert.AreEqual(3, result[2].first, "[2].first");
			Assert.AreEqual(3, result[2].second, "[2].second");
		}

		//Tests the Zip function for the case when the second sequence is shorter.
		TEST_METHOD(ZipSecondShorter)
		{
			auto result = Range(1, 5).Zip(Range(5, 3, -1)).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1, result[0].first, "[0].first");
			Assert.AreEqual(5, result[0].second, "[0].second");
			Assert.AreEqual(2, result[1].first, "[1].first");
			Assert.AreEqual(4, result[1].second, "[1].second");
			Assert.AreEqual(3, result[2].first, "[2].first");
			Assert.AreEqual(3, result[2].second, "[2].second");
		}

		//Tests the Zip function for the case when the sequences are the same length.
		TEST_METHOD(ZipBothSame)
		{
			auto result = Range(1, 3).Zip(Range(5, 3, -1)).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1, result[0].first, "[0].first");
			Assert.AreEqual(5, result[0].second, "[0].second");
			Assert.AreEqual(2, result[1].first, "[1].first");
			Assert.AreEqual(4, result[1].second, "[1].second");
			Assert.AreEqual(3, result[2].first, "[2].first");
			Assert.AreEqual(3, result[2].second, "[2].second");
		}

		//Tests the Zip function for the case when a custom function is used to generate new values from the two sequences.
		TEST_METHOD(ZipWithFunction)
		{
			auto result = Range(1, 3).Zip(Range(5, 3, -1), [](int x, int y){ return x * y; }).ToVector();
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(5, result[0], "[0]");
			Assert.AreEqual(8, result[1], "[1]");
			Assert.AreEqual(9, result[2], "[2]");
		}
	};
}

