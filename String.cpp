#include "String.h"
#include <string>

namespace ObjectLibrary
{
	struct String::Data
	{
		template <typename... T>
		Data(T... args)
			: value(args...)
		{
		}
		std::string value;
	};
	
	String::String()
		: mData(new Data())
	{
	}
	String::String(const String& rhs)
		: mData(new Data(rhs.mData->value))
	{
	}
	String::String(const char* value)
		: mData(new Data(value))
	{
	}
	String::~String()
	{
		delete mData;
	}
	
	String& String::operator=(const String& rhs)
	{
		if (this != &rhs)
			mData->value = rhs.mData->value;
		return *this;
	}
	String& String::operator=(const char* value)
	{
		mData->value = value;
		return *this;
	}

	const std::type_info& String::GetType() const
	{
		return typeid(String);
	}
	String String::ToString() const
	{
		return *this;
	}
	
	const char* String::GetData() const
	{
		return mData->value.c_str();
	}
}

std::ostream& operator<<(std::ostream& out, const ObjectLibrary::String& rhs)
{
	return out << rhs.GetData();
}
