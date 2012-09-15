////////////////////////////////////////////////////////////////////////////////
// Filename:    SelectEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:16
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(SelectEnumeratorTest)
	{
	public:
		SelectEnumeratorTest()
		{
		}

		//Tests the Select function for the case when the functor returns a reference type.
		TEST_METHOD(SelectReference)
		{
			auto source = Range(1, 5).ToVector();
			From(source).Select([](int& value) -> int& { return value; }).ForEach([](int& value)
			{
				++value;
			});
			Assert.AreEqual(5ull, source.size(), "size");
			Assert.AreEqual(2, source[0], "[0]");
			Assert.AreEqual(3, source[1], "[1]");
			Assert.AreEqual(4, source[2], "[2]");
			Assert.AreEqual(5, source[3], "[3]");
			Assert.AreEqual(6, source[4], "[4]");
		}

		//Tests the Select function for the case when the functor returns a copyable result.
		TEST_METHOD(SelectCopy)
		{
			auto result = Range(1, 5).Select([](int value){ return std::make_pair(value > 3, value); }).ToVector();
			Assert.AreEqual(5ull, result.size(), "size");
			Assert.IsFalse(result[0].first, "[0].first");
			Assert.AreEqual(1, result[0].second, "[0].second");
			Assert.IsFalse(result[1].first, "[1].first");
			Assert.AreEqual(2, result[1].second, "[1].second");
			Assert.IsFalse(result[2].first, "[2].first");
			Assert.AreEqual(3, result[2].second, "[2].second");
			Assert.IsTrue(result[3].first, "[3].first");
			Assert.AreEqual(4, result[3].second, "[3].second");
			Assert.IsTrue(result[4].first, "[4].first");
			Assert.AreEqual(5, result[4].second, "[4].second");
		}
	};
}

