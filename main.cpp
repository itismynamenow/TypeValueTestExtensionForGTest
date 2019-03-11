#include <gtest/gtest.h>

//#include "general_example.h"
//#include "lazy_example.h"
#include "applied_example.h"
#include "type_value_pretty_printer.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::UnitTest& unit_test = *::testing::UnitTest::GetInstance();
    ::testing::TestEventListeners& listeners = unit_test.listeners();

    // Removes the default console output listener from the list so it will
    // not receive events from Google Test and won't print any output. Since
    // this operation transfers ownership of the listener to the caller we
    // have to delete it as well.
    delete listeners.Release(listeners.default_result_printer());

    // Adds the custom output listener to the list. It will now receive
    // events from Google Test and print the alternative output. We don't
    // have to worry about deleting it since Google Test assumes ownership
    // over it after adding it to the list.
    listeners.Append(new TypeValuePrettyUnitTestResultPrinter);

    auto testSuiteCount = ::testing::UnitTest::GetInstance()->total_test_suite_count();
    for(int i=0;i<testSuiteCount;i++){
        const auto testSuite = ::testing::UnitTest::GetInstance()->GetTestSuite(i);
    }
    return RUN_ALL_TESTS();
}
