#pragma once
#include "FrontEndedCollection.h"
#include "BackEndedCollection.h"

namespace ObjectLibrary
{
	template <typename T>
	class __declspec(dllexport) DoubleEndedCollection :
		virtual public FrontEndedCollection<T>,
		virtual public BackEndedCollection<T>
	{
	};
}
