#pragma once
#include "TypeInfoHelper.h"

template <typename T, typename TName>
class Property
{
public:
	typedef typename TypeInfoHelper<T>::StorageType StorageType;
	typedef T Type;
	typedef TName NameType;
};
