////////////////////////////////////////////////////////////////////////////////
// Filename:    StaticCastEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:38
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(StaticCastEnumeratorTest)
	{
	public:
		StaticCastEnumeratorTest()
		{
		}

		TEST_METHOD(StaticCastValid)
		{
			auto result = Range(1, 3).Cast<double>().ToVector();
			Assert.IsTrue(typeid(result) == typeid(std::vector<double>), "type");
			Assert.AreEqual(3ull, result.size(), "size");
			Assert.AreEqual(1.0, result[0], "[0]");
			Assert.AreEqual(2.0, result[1], "[1]");
			Assert.AreEqual(3.0, result[2], "[2]");
		}
	};
}

