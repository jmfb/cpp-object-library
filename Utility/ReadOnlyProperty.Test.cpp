////////////////////////////////////////////////////////////////////////////////
// Filename:    ReadOnlyProperty.Test.cpp
// Description: This file defines all ReadOnlyProperty unit tests.
//
// Created:     2012-09-20 00:16:07
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "ReadOnlyProperty.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace ObjectLibrary
{
	TEST_CLASS(ReadOnlyPropertyTest)
	{
	public:
		class Foo
		{
		public:
			int GetValue() const
			{
				return value;
			}
			int value = 0;
		};
		
		ReadOnlyPropertyTest()
			: property(&foo, &Foo::GetValue)
		{
		}

		TEST_METHOD(Constructor)
		{
			Assert.AreEqual(&foo, property.instance, "instance");
			Assert.AreEqual(&Foo::GetValue, property.getFunc, "getFunc");
		}

		TEST_METHOD(GetValue)
		{
			const auto value = 123;
			foo.value = value;
			int result = property;
			Assert.AreEqual(value, result);
		}

	private:
		Foo foo;
		decltype(MakeProperty(&Foo::GetValue)) property;
	};
}

