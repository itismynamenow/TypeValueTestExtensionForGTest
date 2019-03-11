#ifndef CONCRETE_EXAMPLE_H
#define CONCRETE_EXAMPLE_H
#include <functional>
#include <algorithm>
#include <vector>
#include <stdlib.h>     /* srand, rand */

#include <gtest/gtest.h>

#include "type_value_test.h"
#include "things_to_test.h"

/// In applied_example.h we turned sorting functions from things_to_test.h
/// into classes derived from abstract SortingAlgorithm class which allowed us to
/// use polymorphism to test all of them. However that approach required us
/// creating that class hierarchy and writing another helping code.
///
/// What if we are lazy or want to test our sorting function without
/// any modifications? Well, below is one way to do it. Of course it
/// will be pretty ugly and dangerous, but that's fine for test I guess

template<typename T>
struct SortTest;
template<typename ...T>
struct SortTest<std::tuple<T...>>
{
    using Types = ::testing::Types<T...>;
};

/// Global array below holds values that we will use in tests
/// GET_VALUE_ID(0) macro will be used in test case to get index
/// from 0 to 2 that will be used to obtain value from this array
constexpr std::array<std::size_t,3> vector_sizes {0,1,10};


/// Below we declare types that we will used in tests
using lessOperatorSortingTypesTuples = std::tuple<std::tuple<int,unsigned,double,ElementWithLessOperator>>;
using comparatorSortingTypesTuples = std::tuple<std::tuple<ElementWithComparator>>;
using valueTuplesSorting = std::tuple<TT::NUM<vector_sizes.size()>>;


/// Below we generate type/valueId permutations
using LessOperatorSortingTypes = TT::getPermutations<lessOperatorSortingTypesTuples,valueTuplesSorting>::tuple;
using ComparatorSortingTypes = TT::getPermutations<comparatorSortingTypesTuples,valueTuplesSorting>::tuple;

/// Macro below exists to prevent problems that occure when we pass one
/// macro into another. In such case if another macro uses ## or # first
/// macro will not be expanded. To address the issue such proxy macro is used
#define TEMPLATED_TEST(...) TYPED_TEST(__VA_ARGS__)

#define TEMPLATED_TEST_SUITE(...) TYPED_TEST_SUITE_MODED(__VA_ARGS__);

/// Some strange code below replaces PLACEHOLDER macro with
/// names of our sorting functions and pastes test code
/// over and over again buy abusing #include "lazy_example.h"
/// Basically after preprocessing there will be 4 copies of code
/// after header guard with PLACEHOLDER() replaced by bubbleSort
/// then by selectionSort then by mergeSort and finally by insertionSort

#define PLACEHOLDER(postfix) bubbleSort ## postfix
#include "lazy_example.h"
#undef PLACEHOLDER
#define PLACEHOLDER(postfix) selectionSort ## postfix
#include "lazy_example.h"
#undef PLACEHOLDER
#define PLACEHOLDER(postfix) mergeSort ## postfix
#include "lazy_example.h"
#undef PLACEHOLDER
#define PLACEHOLDER(postfix) insertionSort ## postfix

///Header guard must be closed here so we can include code below as
///many times as we need and code below must allow multiple inclusion
#endif // CONCRETE_EXAMPLE_H

template <typename T>
class PLACEHOLDER(Test0) : public ::testing::Test {};

TEMPLATED_TEST_SUITE(PLACEHOLDER(Test0), LessOperatorSortingTypes, TT::NameGenerator)

TEMPLATED_TEST(PLACEHOLDER(Test0), LessOperatorSorting)
{
    using TYPE0 = GET_TYPE(0);
    const auto valueId0 = GET_VALUE_ID(0);
    const auto value0 = vector_sizes.at(valueId0);
    auto vec = makeRandomVector<TYPE0>(value0);
    PLACEHOLDER()(vec.begin(),vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(),vec.end()));
}

template <typename T>
class PLACEHOLDER(Test1) : public ::testing::Test {};

TEMPLATED_TEST_SUITE(PLACEHOLDER(Test1), ComparatorSortingTypes, TT::NameGenerator)

TEMPLATED_TEST(PLACEHOLDER(Test1), ComparatorSorting)
{
    using TYPE0 = GET_TYPE(0);
    const auto valueId0 = GET_VALUE_ID(0);
    const auto value0 = vector_sizes.at(valueId0);
    auto vec = makeRandomVector<TYPE0>(value0);
    PLACEHOLDER()(vec.begin(),vec.end(),TYPE0::getComparator());
    ASSERT_TRUE(std::is_sorted(vec.begin(),vec.end(),TYPE0::getComparator()));
    std::vector<int> vecInt;
    for(const auto &element: vec){
        vecInt.push_back(element.value);
    }
    ASSERT_TRUE(std::is_sorted(vecInt.begin(),vecInt.end()));
}










