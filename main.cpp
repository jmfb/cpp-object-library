#include <iostream>
#include "StringTemplate.h"
#include "StringTemplateCat.h"

namespace StringTable
{
	typedef _ST("Foo", 3) Foo;
	typedef _ST("Bar", 3) Bar;
	typedef _ST("Value", 5) Value;
	typedef typename StringTemplateCat<Foo, _ST(".", 1), Bar>::Type Foo_Bar;
	typedef _ST("012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678", 99) LongExample;
}

int main(int argc, char** argv)
{
	std::cout << StringTable::Foo::Get() << std::endl;
	std::cout << StringTable::LongExample::Get() << std::endl;
	std::cout << StringTable::Foo_Bar::Get() << std::endl;
	return 0;
}
