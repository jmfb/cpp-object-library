////////////////////////////////////////////////////////////////////////////////
// Filename:    GroupByEnumerator.Test.cpp
// Description: This file declares all GroupByEnumerator unit tests.
//
// Created:     2012-09-20 00:43:47
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "Enumerator.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Linq
{
	TEST_CLASS(GroupByEnumeratorTest)
	{
	public:
		GroupByEnumeratorTest()
		{
		}

		TEST_METHOD(GroupByEvenOdd)
		{
			std::vector<std::pair<int, std::vector<int>>> data;
			auto result = Range(1, 5).GroupBy([](int value){ return value % 2; });
			result.ForEach([&data](decltype(result)::ValueType group)
			{
				data.push_back({ group.GetKey(), group.ToVector() });
			});
			std::vector<std::pair<int, std::vector<int>>> expected = {
				{ 0, { 2, 4 } },
				{ 1, { 1, 3, 5 } }
			};
			Assert.IsTrue(expected == data);
		}

		TEST_METHOD(GroupByWithReference)
		{
			std::vector<int> source { 1, 2, 3, 4, 5 };
			const std::vector<int> expected { 1, 0, 3, 0, 5 };
			auto result = From(source).GroupBy([](int value){ return value % 2; });
			result.Single([](decltype(result)::ValueType group){ return group.GetKey() == 0; })
				.ForEach([](int& value){ value = 0; });
			Assert.IsTrue(expected == source);
		}

		TEST_METHOD(GroupByToSort)
		{
			const std::vector<int> expected = { 2, 4, 1, 3, 5 };
			auto result = Range(1, 5).GroupBy([](int value){ return value % 2; });
			auto actual = result.SelectMany([](decltype(result)::ValueType group){ return group; }).ToVector();
			Assert.IsTrue(expected == actual);
		}
	};
}

