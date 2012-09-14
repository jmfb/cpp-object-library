#pragma once
#include "Container.h"

namespace ObjectLibrary
{
	template <typename T>
	class __declspec(dllexport) FrontEndedCollection : virtual public Container
	{
	public:
		virtual void PushFront(const T& value) = 0;
		virtual void PopFront() = 0;
	};
}
