////////////////////////////////////////////////////////////////////////////////
// Filename:    WriteOnlyProperty.Test.cpp
// Description: This file defines all WriteOnlyProperty unit tests.
//
// Created:     2012-09-20 00:26:04
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "WriteOnlyProperty.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace ObjectLibrary
{
	TEST_CLASS(WriteOnlyPropertyTest)
	{
	public:
		class Foo
		{
		public:
			void SetValue(int value)
			{
				this->value = value;
			}
			int value = 0;
		};
		
		WriteOnlyPropertyTest()
			: property(&foo, &Foo::SetValue)
		{
		}

		TEST_METHOD(Constructor)
		{
			Assert.AreEqual(&foo, property.instance, "instance");
			Assert.AreEqual(&Foo::SetValue, property.setFunc, "setFunc");
		}

		TEST_METHOD(SetValue)
		{
			const auto value = 123;
			Assert.AreNotEqual(value, foo.value, "initial");
			auto& result = (property = value);
			Assert.AreEqual(value, foo.value, "final");
			Assert.AreEqual(&property, &result, "result");
		}

	private:
		Foo foo;
		decltype(MakeProperty(&Foo::SetValue)) property;
	};
}

