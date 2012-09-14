#pragma once
#include "Container.h"

namespace ObjectLibrary
{
	template <typename T>
	class __declspec(dllexport) BackEndedCollection : virtual public Container
	{
	public:
		virtual void PushBack(const T& value) = 0;
		virtual void PopBack() = 0;
	};
}
