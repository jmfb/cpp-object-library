#pragma once
#include "Container.h"

namespace ObjectLibrary
{
	template <typename T>
	class __declspec(dllexport) EndedCollection : virtual public Container<T>
	{
	public:
		virtual const T& GetFront() const = 0;
		virtual T& GetFront() = 0;
		virtual void SetFront(const T& value) = 0;
		virtual const T& GetBack() const = 0;
		virtual T& GetBack() = 0;
		virtual void SetBack(const T& value) = 0;
	};
}
