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
		: data(new Data())
	{
	}
	String::String(const String& rhs)
		: data(new Data(rhs.data->value))
	{
	}
	String::String(const char* const value)
		: data(new Data(value))
	{
	}
	String::~String()
	{
		delete data;
	}
	
	String& String::operator=(const String& rhs)
	{
		if (this != &rhs)
			data->value = rhs.data->value;
		return *this;
	}
	String& String::operator=(const char* const value)
	{
		data->value = value;
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
		return data->value.c_str();
	}
}

std::ostream& operator<<(std::ostream& out, const ObjectLibrary::String& rhs)
{
	return out << rhs.GetData();
}
