#ifndef CONCRETE_EXAMPLE_H
#define CONCRETE_EXAMPLE_H
#include <functional>
#include <algorithm>
#include <vector>
#include <stdlib.h>     /* srand, rand */

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "type_value_test.h"

//In this example we will test template sort function
//To test it well it is necessary to run it with
//vectors of different types and sizes
template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
void selectionSort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()){
    if(first == last || std::next(first) == last) return;
    for(auto iterator = first;iterator!=last;++iterator){
        const auto minValueIterator = std::min_element(iterator,last,comparator);
        std::swap(*iterator,*minValueIterator);
    }
};

template<class T>
std::vector<T>makeCustomVector(int size){
    std::vector<T> vec(size);
    for(auto &element: vec){
        element = rand() % 1000;
    }
    return vec;
}


template<typename T>
struct SortTest;
template<typename ...T>
struct SortTest<std::tuple<T...>>
{
    using Types = ::testing::Types<T...>;
};
template <typename T>
class TypedSortTest : public ::testing::Test {};

constexpr std::array<std::size_t,3> vector_sizes {0,1,10};

using typesTuplesSorting = std::tuple<std::tuple<int,unsigned,double>>;
using valueTuplesSorting = std::tuple<TVT::NUM<vector_sizes.size()>>;

using TestTypes = SortTest<TVT::getPermutations<typesTuplesSorting,valueTuplesSorting>::tuple>::Types;

TYPED_TEST_CASE(TypedSortTest, TestTypes);

TYPED_TEST(TypedSortTest, sizeCheck)
{
    using TYPE0 = typename std::tuple_element<0, typename TypeParam::types>;
    const std::size_t value_id_0 = std::tuple_element<0, typename TypeParam::valuesId>::type::value;
    std::vector<TYPE0> vec = makeCustomVector<TYPE0>(vector_sizes.at(value_id_0));
    ASSERT_TRUE(vec.size() == vector_sizes.at(value_id_0));
    selectionSort(vec.begin(),vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(),vec.end()));
    ASSERT_TRUE(vec.size() == vector_sizes.at(value_id_0));
}

#endif // CONCRETE_EXAMPLE_H
