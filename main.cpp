#include "general_example.h"
#include "lazy_example.h"
#include "applied_example.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    auto testSuiteCount = ::testing::UnitTest::GetInstance()->total_test_suite_count();
    for(int i=0;i<testSuiteCount;i++){
        const auto testSuite = ::testing::UnitTest::GetInstance()->GetTestSuite(i);
    }
    return RUN_ALL_TESTS();
}
