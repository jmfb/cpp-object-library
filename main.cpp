#include <iostream>
#include "Enumerator.h"

int main(int argc, char** argv)
{
	auto displayInt = [](int value){ std::cout << value << std::endl; };
	
	Linq::Repeat(123, 5).ForEach(displayInt);
	std::cout << Linq::Repeat(1, 2).First() << std::endl;
	Linq::Range(2, 5, 2).ForEach(displayInt);

	std::vector<int> vec { 1, 2, 3, 4, 5 };
	Linq::From(vec)
		.Where([](int value){ return value > 3; })
		.ForEach(displayInt);

	auto vecPair = Linq::Range(1, 5).Select([](int value){ return std::make_pair(true, value); }).ToVector();
	for (auto item: vecPair)
		std::cout << item.second << std::endl;
		
	std::cout << "Press enter to continue...";
	std::cin.get();
	return 0;
}

