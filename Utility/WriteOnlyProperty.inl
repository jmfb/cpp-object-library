////////////////////////////////////////////////////////////////////////////////
// Filename:    WriteOnlyProperty.inl
// Description: This file implements all WriteOnlyProperty member functions.
//
// Created:     2012-09-20 00:26:04
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "WriteOnlyProperty.h"

namespace ObjectLibrary
{
	template <typename ClassType, typename SetType>
	inline WriteOnlyProperty<ClassType, SetType>::WriteOnlyProperty(
		ClassType* instance,
		SetFuncType setFunc)
		: instance(instance), setFunc(setFunc)
	{
	}

	template <typename ClassType, typename SetType>
	inline WriteOnlyProperty<ClassType, SetType>&
		WriteOnlyProperty<ClassType, SetType>::operator=(SetType value)
	{
		(instance->*setFunc)(value);
		return *this;
	}
}

