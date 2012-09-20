////////////////////////////////////////////////////////////////////////////////
// Filename:    ReadOnlyProperty.inl
// Description: This file implements all ReadOnlyProperty member functions.
//
// Created:     2012-09-20 00:16:07
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "ReadOnlyProperty.h"

namespace ObjectLibrary
{
	template <typename ClassType, typename GetType>
	inline ReadOnlyProperty<ClassType, GetType>::ReadOnlyProperty(
		ClassType* instance,
		GetFuncType getFunc)
		: instance(instance), getFunc(getFunc)
	{
	}

	template <typename ClassType, typename GetType>
	inline ReadOnlyProperty<ClassType, GetType>::operator GetType() const
	{
		return (instance->*getFunc)();
	}
}

