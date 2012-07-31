#include <iostream>
#include "String.h"

int main(int argc, char** argv)
{
	ObjectLibrary::String value(argc > 0 ? argv[0] : "null");
	std::cout << value << std::endl;
	return 0;
}
