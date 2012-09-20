////////////////////////////////////////////////////////////////////////////////
// Filename:    WriteOnlyProperty.h
// Description: This file declares the WriteOnlyProperty class.
//
// Created:     2012-09-20 00:26:04
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace ObjectLibrary
{
	template <typename ClassType, typename SetType>
	class WriteOnlyProperty
	{
	public:
		typedef WriteOnlyProperty<ClassType, SetType> PropertyType;
		typedef void (ClassType::*SetFuncType)(SetType);
		
		WriteOnlyProperty(ClassType* instance, SetFuncType setFunc);
		WriteOnlyProperty(const PropertyType& rhs) = delete;
		~WriteOnlyProperty() = default;

		PropertyType& operator=(const PropertyType& rhs) = delete;
		PropertyType& operator=(SetType value);

	private:
		friend class WriteOnlyPropertyTest;
		ClassType* instance = nullptr;
		SetFuncType setFunc = nullptr;
	};

	template <typename ClassType, typename SetType>
	WriteOnlyProperty<ClassType, SetType> MakeProperty(
		void (ClassType::*)(SetType));
}

#include "WriteOnlyProperty.inl"

