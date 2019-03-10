//#include "general_example.h"
//#include "concrete_example.h"
#include "applied_example.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
