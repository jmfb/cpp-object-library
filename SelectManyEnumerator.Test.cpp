////////////////////////////////////////////////////////////////////////////////
// Filename:    SelectManyEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:19
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(SelectManyEnumeratorTest)
	{
	public:
		SelectManyEnumeratorTest()
		{
		}

		TEST_METHOD(SelectMany)
		{
			auto result = Range(1, 3).SelectMany([](int value){ return Repeat(value, 2); }).ToVector();
			Assert.AreEqual(6ull, result.size(), "size");
			Assert.AreEqual(1, result[0], "[0]");
			Assert.AreEqual(1, result[1], "[1]");
			Assert.AreEqual(2, result[2], "[2]");
			Assert.AreEqual(2, result[3], "[3]");
			Assert.AreEqual(3, result[4], "[4]");
			Assert.AreEqual(3, result[5], "[5]");
		}
	};
}

