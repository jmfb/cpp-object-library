////////////////////////////////////////////////////////////////////////////////
// Filename:    ReadOnlyProperty.h
// Description: This file declares the ReadOnlyProperty class.
//
// Created:     2012-09-20 00:16:07
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace ObjectLibrary
{
	template <typename ClassType, typename GetType>
	class ReadOnlyProperty
	{
	public:
		typedef ReadOnlyProperty<ClassType, GetType> PropertyType;
		typedef GetType (ClassType::*GetFuncType)() const;
		
		ReadOnlyProperty(ClassType* instance, GetFuncType getFunc);
		ReadOnlyProperty(const PropertyType& rhs) = delete;
		~ReadOnlyProperty() = default;

		PropertyType& operator=(const PropertyType& rhs) = delete;

		operator GetType() const;
		
	private:
		friend class ReadOnlyPropertyTest;
		ClassType* instance = nullptr;
		GetFuncType getFunc = nullptr;
	};

	template <typename ClassType, typename GetType>
	ReadOnlyProperty<ClassType, GetType> MakeProperty(
		GetType (ClassType::*)() const);
}

#include "ReadOnlyProperty.inl"

