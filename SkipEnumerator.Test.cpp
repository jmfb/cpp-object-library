////////////////////////////////////////////////////////////////////////////////
// Filename:    SkipEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:22
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(SkipEnumeratorTest)
	{
	public:
		SkipEnumeratorTest()
		{
		}

		//Tests the Skip function for the case when not skipping anything.
		TEST_METHOD(SkipNone)
		{
			auto source = Range(1, 3).Skip(0).ToVector();
			Assert.AreEqual(3ull, source.size(), "size");
			Assert.AreEqual(1, source[0], "[0]");
			Assert.AreEqual(2, source[1], "[1]");
			Assert.AreEqual(3, source[2], "[2]");
		}
		
		//Tests the Skip function for the case when skipping a valid number of items.
		TEST_METHOD(SkipValid)
		{
			auto source = Range(1, 5).Skip(2).ToVector();
			Assert.AreEqual(3ull, source.size(), "size");
			Assert.AreEqual(3, source[0], "[0]");
			Assert.AreEqual(4, source[1], "[1]");
			Assert.AreEqual(5, source[2], "[2]");
		}

		//Tests the Skip function for the case when skipping all or more of the sequence.
		TEST_METHOD(SkipAll)
		{
			auto source = Range(1, 5).Skip(5).ToVector();
			Assert.IsTrue(source.empty());
		}
	};
}


