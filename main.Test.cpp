////////////////////////////////////////////////////////////////////////////////
// Filename:    main.Test.cpp
// Description: Unit test main entry point.
//
// Created:     2012-09-14 00:49:06
// Author:      Jacob Buysse
////////////////////////////////////////////////////////////////////////////////
#include <UnitTest/UnitTest.h>

int main(int argc, char** argv)
{
	UnitTest::TestRunner::RunTestsFromCommandLine(argc, argv);
	return 0;
}

