#pragma once
#include "Object.h"

namespace ObjectLibrary
{
	//The String class is a dll-safe version of the STL std::string class.  Class libraries
	//should use this class in interface design to avoid coupling to different STL versions
	//of the std::string class.
	class __declspec(dllexport) String : virtual public Object
		//TODO: more enumerable and container interfaces supported (as Vector<char>)
	{
	public:
		String();
		String(const String& rhs);
		String(const char* const value);
		virtual ~String();
		
		String& operator=(const String& rhs);
		String& operator=(const char* const value);
		
		virtual const std::type_info& GetType() const;
		virtual String ToString() const;
		
		const char* GetData() const;
		
	private:
		struct Data;
		Data* data;
	};
}

//Custom implementation of the stream insertion operator for String.  This avoids the infinite
//recursion problem of allowing the Object stream insertion to recursively call ToString.
__declspec(dllexport) std::ostream& operator<<(std::ostream& out, const ObjectLibrary::String& rhs);
