#include "general_example.h"
#include "lazy_example.h"
#include "applied_example.h"

#include <gtest/gtest.h>

class TersePrinter : public ::testing::EmptyTestEventListener {
 private:
  // Called before any test activity starts.
  void OnTestProgramStart(const ::testing::UnitTest& /* unit_test */) override {}

  // Called after all test activities have ended.
  void OnTestProgramEnd(const ::testing::UnitTest& unit_test) override {
    fprintf(stdout, "TEST %s\n", unit_test.Passed() ? "PASSED" : "FAILED");
    fflush(stdout);
  }

  // Called before a test starts.
  void OnTestStart(const ::testing::TestInfo& test_info) override {
    fprintf(stdout,
            "*** Test %s.%s starting.\n",
            test_info.test_case_name(),
            test_info.name());
    fflush(stdout);
  }

  // Called after a failed assertion or a SUCCEED() invocation.
  void OnTestPartResult(const ::testing::TestPartResult& test_part_result) override {
    fprintf(stdout,
            "%s in %s:%d\n%s\n",
            test_part_result.failed() ? "*** Failure" : "Success",
            test_part_result.file_name(),
            test_part_result.line_number(),
            test_part_result.summary());
    fflush(stdout);
  }

  // Called after a test ends.
  void OnTestEnd(const ::testing::TestInfo& test_info) override {
    fprintf(stdout,
            "*** Test %s.%s ending.\n",
            test_info.test_case_name(),
            test_info.name());
    fflush(stdout);
  }
}; // class TersePrinter

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
    listeners.Append(new TersePrinter);

    auto testSuiteCount = ::testing::UnitTest::GetInstance()->total_test_suite_count();
    for(int i=0;i<testSuiteCount;i++){
        const auto testSuite = ::testing::UnitTest::GetInstance()->GetTestSuite(i);
    }
    return RUN_ALL_TESTS();
}
