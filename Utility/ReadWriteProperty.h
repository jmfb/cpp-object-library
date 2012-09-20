////////////////////////////////////////////////////////////////////////////////
// Filename:    ReadWriteProperty.h
// Description: This file declares the ReadWriteProperty class.
//
// Created:     2012-09-19 23:47:37
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace ObjectLibrary
{
	template <typename ClassType, typename GetType, typename SetType>
	class ReadWriteProperty
	{
	public:
		typedef ReadWriteProperty<ClassType, GetType, SetType> PropertyType;
		typedef GetType (ClassType::*GetFuncType)() const;
		typedef void (ClassType::*SetFuncType)(SetType);

		ReadWriteProperty(ClassType* instance, GetFuncType getFunc, SetFuncType setFunc);
		ReadWriteProperty(const PropertyType& rhs) = delete;
		~ReadWriteProperty() = default;

		PropertyType& operator=(const PropertyType& rhs) = delete;
		PropertyType& operator=(SetType value);

		operator GetType() const;

	private:
		friend class ReadWritePropertyTest;
		ClassType* instance = nullptr;
		GetFuncType getFunc = nullptr;
		SetFuncType setFunc = nullptr;
	};

	template <typename ClassType, typename GetType, typename SetType>
	ReadWriteProperty<ClassType, GetType, SetType> MakeProperty(
		GetType (ClassType::*)() const,
		void (ClassType::*)(SetType));
}

#include "ReadWriteProperty.inl"

