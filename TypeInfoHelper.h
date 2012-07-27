#pragma once
#include <memory>

template <typename T>
class TypeInfoHelper
{
public:
	typedef T StorageType;
};

template <typename T>
class TypeInfoHelper<T*>
{
public:
	typedef std::shared_ptr<typename TypeInfoHelper<T>::StorageType> StorageType;
};
