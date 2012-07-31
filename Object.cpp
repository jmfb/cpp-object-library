#include "Object.h"
#include "String.h"

namespace ObjectLibrary
{
	Object::~Object()
	{
		//nothing
	}

	String Object::ToString() const
	{
		return GetType().name();
	}
}

std::ostream& operator<<(std::ostream& out, const ObjectLibrary::Object& rhs)
{
	return out << rhs.ToString();
}
