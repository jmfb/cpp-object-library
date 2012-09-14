#pragma once
#include "Object.h"

namespace ObjectLibrary
{
	class __declspec(dllexport) Container : virtual public Object
	{
	public:
		virtual bool IsEmpty() const = 0;
		virtual unsigned long GetSize() const = 0;
	};
}
