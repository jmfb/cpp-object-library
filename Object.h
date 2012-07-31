#pragma once
#include <typeinfo>
#include <iostream>

namespace ObjectLibrary
{
	//Forward declare String.  This is needed because all ObjectLibrary classes and
	//interfaces will derive from Object but Object has the ToString function which
	//will return the String type.
	class String;

	//Base Object class for all ObjectLibrary classes and interfaces.  Derivation for
	//this class and all interfaces should be virtual.  The destructor is virtual so
	//it is safe to delete through any pointer within the class hierarchy.  All derived
	//types must implement GetType to return typeid(T).  All derived types may optionally
	//override the ToString functionality which will by default return the name of the type.
	class __declspec(dllexport) Object
	{
	public:
		virtual ~Object();
		
		virtual const std::type_info& GetType() const = 0;
		virtual String ToString() const;
	};
}

//Support for writing objects to STL streams are supported via the ToString function.
__declspec(dllexport) std::ostream& operator<<(std::ostream& out, const ObjectLibrary::Object& rhs);
