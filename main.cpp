#include <iostream>
#include "StringTemplate.h"
#include "StringTemplateCat.h"
#include "Property.h"
#include "Entity.h"
#include "EntityInstance.h"

namespace StringTable
{
	typedef _ST("Bar", 3) Bar;
	typedef _ST("Foo", 3) Foo;
	typedef _ST("Key", 3) Key;
	typedef _ST("Value", 5) Value;
	typedef _ST("Child", 5) Child;
}

typedef Entity<StringTable::Bar,
	Property<int, StringTable::Value>
> Bar;

typedef Entity<StringTable::Foo,
	Property<int, StringTable::Key>,
	Property<int, StringTable::Value>,
	Property<Bar*, StringTable::Child>
> Foo;

int main(int argc, char** argv)
{
	EntityInstance<Foo> foo;
	foo.Get<StringTable::Key>() = 3;
	foo.Get<StringTable::Value>() = 5;
	foo.Get<StringTable::Child>().reset(new EntityInstance<Bar>());
	foo.Get<StringTable::Child>()->Get<StringTable::Value>() = 9;
	std::cout << foo.Get<StringTable::Key>() << " = " << foo.Get<StringTable::Value>() << std::endl;
	return 0;
}
