////////////////////////////////////////////////////////////////////////////////
// Filename:    IteratorEnumerator.Test.cpp
// Description: ...
//
// Created:     2012-09-15 13:47:08
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(IteratorEnumeratorTest)
	{
	public:
		IteratorEnumeratorTest()
		{
		}

		TEST_METHOD(FromRange)
		{
			const auto source = Range(1, 5).ToVector();
			std::size_t count = 0;
			auto next = 2;
			From(source.begin() + 1, source.begin() + 4).ForEach([&count, &next](int value)
			{
				Assert.AreEqual(next, value, "value");
				++next;
				++count;
			});
			Assert.AreEqual(3ull, count, "count");
		}

		TEST_METHOD(FromContainer)
		{
			const auto initial = 1;
			const std::size_t count = 5;
			auto source = Range(initial, count).ToVector();
			auto next = initial;
			std::size_t result = 0;
			From(source).ForEach([&next, &result](int& value)
			{
				Assert.AreEqual(next, value, "value");
				++value;
				++next;
				++result;
			});
			Assert.AreEqual(count, result, "count");
			next = initial + 1;
			From(source).ForEach([&next](int value)
			{
				Assert.AreEqual(next, value, "value(modified)");
				++next;
			});
		}

		TEST_METHOD(FromConstContainer)
		{
			const auto initial = 1;
			const std::size_t count = 5;
			const auto source = Range(initial, count).ToVector();
			auto next = initial;
			std::size_t result = 0;
			From(source).ForEach([&next, &result](const int& value)
			{
				Assert.AreEqual(next, value, "value");
				++next;
				++result;
			});
			Assert.AreEqual(count, result, "count");
		}

		TEST_METHOD(FromConstContainerExplicit)
		{
			const auto initial = 1;
			const std::size_t count = 5;
			auto source = Range(initial, count).ToVector();
			auto next = initial;
			std::size_t result = 0;
			FromConst(source).ForEach([&next, &result](const int& value)
			{
				Assert.AreEqual(next, value, "value");
				++next;
				++result;
			});
			Assert.AreEqual(count, result, "count");
		}

		TEST_METHOD(FromContainerReverse)
		{
			const auto initial = 1;
			const std::size_t count = 5;
			auto source = Range(initial, count).ToVector();
			auto next = static_cast<int>(initial + count - 1);
			std::size_t result = 0;
			FromReverse(source).ForEach([&next, &result](int& value)
			{
				Assert.AreEqual(next, value, "value");
				++value;
				--next;
				++result;
			});
			Assert.AreEqual(count, result, "count");
			next = initial + 1;
			From(source).ForEach([&next](int value)
			{
				Assert.AreEqual(next, value, "value(modified)");
				++next;
			});
		}

		TEST_METHOD(FromConstContainerReverse)
		{
			const auto initial = 1;
			const std::size_t count = 5;
			const auto source = Range(initial, count).ToVector();
			auto next = static_cast<int>(initial + count - 1);
			std::size_t result = 0;
			FromReverse(source).ForEach([&next, &result](const int& value)
			{
				Assert.AreEqual(next, value, "value");
				--next;
				++result;
			});
			Assert.AreEqual(count, result, "count");
		}

		TEST_METHOD(FromConstContainerExplicitReverse)
		{
			const auto initial = 1;
			const std::size_t count = 5;
			auto source = Range(initial, count).ToVector();
			auto next = static_cast<int>(initial + count - 1);
			std::size_t result = 0;
			FromConstReverse(source).ForEach([&next, &result](const int& value)
			{
				Assert.AreEqual(next, value, "value");
				--next;
				++result;
			});
			Assert.AreEqual(count, result, "count");
		}
	};
}

