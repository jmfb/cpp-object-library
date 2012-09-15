////////////////////////////////////////////////////////////////////////////////
// Filename:    WhereEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:12
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(WhereEnumeratorTest)
	{
	public:
		WhereEnumeratorTest()
		{
		}

		//Tests the Where function for the case when no matches are found.
		TEST_METHOD(WhereNone)
		{
			auto result = Range(1, 5).Where([](int value){ return value > 5; }).ToVector();
			Assert.AreEqual(0ull, result.size());
		}

		//Tests the Where function for the case when valid.
		TEST_METHOD(WhereValid)
		{
			auto result = Range(1, 5).Where([](int value){ return value > 3; }).ToVector();
			Assert.AreEqual(2ull, result.size(), "size");
			Assert.AreEqual(4, result[0], "[0]");
			Assert.AreEqual(5, result[1], "[1]");
		}
	};
}

