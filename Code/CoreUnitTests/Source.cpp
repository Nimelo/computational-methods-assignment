#include <iostream>
#include <vld.h>

#include "gtest/gtest.h"
#include "Configuration.h"

int main(int argc, char** argv)
{
	{
		testing::InitGoogleTest(&argc, argv);
		RUN_ALL_TESTS();
		std::getchar();
	}
}