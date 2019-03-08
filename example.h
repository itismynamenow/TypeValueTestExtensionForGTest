#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "type_value_test.h"

template<typename T>
struct Test;

template<typename ...T>
struct Test<std::tuple<T...>>
{
    using Types = ::testing::Types<T...>;
};

template <typename T>
class TypedTest : public ::testing::Test {};

struct A{};
struct B{};
struct C{};
struct D{};
struct E{};
struct F{};

using typesTuples = std::tuple<std::tuple<A,B,C>,std::tuple<A,B>>;
using valueTuples = std::tuple<TVT::NUM<3>,TVT::NUM<2>>;

using TestTypes = Test<TVT::getPermutations<typesTuples,valueTuples>::tuple>::Types;

TYPED_TEST_CASE(TypedTest, TestTypes);

TYPED_TEST(TypedTest, printTypes)
{
    using TYPE0 = typename std::tuple_element<0, typename TypeParam::types>;
    using TYPE1 = typename std::tuple_element<1, typename TypeParam::types>;
    const std::size_t value_id_0 = std::tuple_element<0, typename TypeParam::valuesId>::type::value;
    const std::size_t value_id_1 = std::tuple_element<1, typename TypeParam::valuesId>::type::value;

    std::cout<<" Types: "<<typeid (typename TYPE0::type).name() <<" "<<typeid (typename TYPE1::type).name()<<" valuesId: "<<value_id_0<<" "<<value_id_1<<std::endl;
}
