////////////////////////////////////////////////////////////////////////////////
// Filename:    ReadWriteProperty.inl
// Description: This file implements all ReadWriteProperty member functions.
//
// Created:     2012-09-19 23:47:37
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "ReadWriteProperty.h"

namespace ObjectLibrary
{
	template <typename ClassType, typename GetType, typename SetType>
	inline ReadWriteProperty<ClassType, GetType, SetType>::ReadWriteProperty(
		ClassType* instance,
		GetFuncType getFunc,
		SetFuncType setFunc)
		: instance(instance), getFunc(getFunc), setFunc(setFunc)
	{
	}

	template <typename ClassType, typename GetType, typename SetType>
	inline ReadWriteProperty<ClassType, GetType, SetType>::operator GetType() const
	{
		return (instance->*getFunc)();
	}

	template <typename ClassType, typename GetType, typename SetType>
	inline ReadWriteProperty<ClassType, GetType, SetType>&
		ReadWriteProperty<ClassType, GetType, SetType>::operator=(SetType value)
	{
		(instance->*setFunc)(value);
		return *this;
	}
}

