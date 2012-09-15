#include <iostream>
#include "Enumerator.h"

int main(int argc, char** argv)
{
	Linq::Range(1, 10)
		.Concat(Linq::Range(9, 9, -1))
		.Skip(1)
		.SkipWhile([](int value){ return value % 2 == 0; })
		.Take(16)
		.TakeWhile([](int value){ return value != 2; })
		.Where([](int value){ return value > 3; })
		.Where([](int value){ return value < 6; })
		.Select([](int value){ return value - 3; })
		.ForEach([](int value){ std::cout << value << std::endl; });

	std::cout << "Press enter to continue...";
	std::cin.get();
	return 0;
}

