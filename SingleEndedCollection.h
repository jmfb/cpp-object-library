#pragma once
#include "Container.h"

namespace ObjectLibrary
{
	template <typename T>
	class __declspec(dllexport) SingleEndedCollection : virtual public Container
	{
	public:
		virtual void Push(const T& value) = 0;
		virtual void Pop() = 0;
		virtual const T& GetNext() const = 0;
		virtual T& GetNext() = 0;
	};
}
