////////////////////////////////////////////////////////////////////////////////
// Filename:    ReadWriteProperty.Test.cpp
// Description: This file defines all ReadWriteProperty unit tests.
//
// Created:     2012-09-19 23:47:37
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include "ReadWriteProperty.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace ObjectLibrary
{
	TEST_CLASS(ReadWritePropertyTest)
	{
	public:
		class Foo
		{
		public:
			int GetValue() const
			{
				return value;
			}
			void SetValue(int value)
			{
				this->value = value;
			}
			int value = 0;
		};

		ReadWritePropertyTest()
			: property(&foo, &Foo::GetValue, &Foo::SetValue)
		{
		}

		TEST_METHOD(Constructor)
		{
			Assert.AreEqual(&foo, property.instance, "instance");
			Assert.AreEqual(&Foo::GetValue, property.getFunc, "getFunc");
			Assert.AreEqual(&Foo::SetValue, property.setFunc, "setFunc");
		}

		TEST_METHOD(GetValue)
		{
			const auto value = 123;
			foo.value = 123;
			int result = property;
			Assert.AreEqual(value, result);
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
		decltype(MakeProperty(&Foo::GetValue, &Foo::SetValue)) property;
	};
}

