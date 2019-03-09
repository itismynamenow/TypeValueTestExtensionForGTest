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

template<class ITERATOR, class COMPARATOR = std::less<typename std::iterator_traits<ITERATOR>::value_type>>
void insertionSort(const ITERATOR first,const ITERATOR last, const COMPARATOR comparator = COMPARATOR ()){
    if(first == last || std::next(first) == last) return;
    for(auto iterator = std::next(first);iterator!=last;++iterator){
        const auto insertionIterator = std::upper_bound(first,iterator,*iterator,comparator);
        std::rotate(insertionIterator,iterator,std::next(iterator));
    }
};

template<class T>
std::vector<T>makeRandomVector(int size){
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

constexpr std::array<std::size_t,3> vector_sizes {0,1,10};

using typesTuplesSorting = std::tuple<std::tuple<int,unsigned,double>>;
using valueTuplesSorting = std::tuple<TVT::NUM<vector_sizes.size()>>;

using TestTypes = SortTest<TVT::getPermutations<typesTuplesSorting,valueTuplesSorting>::tuple>::Types;

#define MY_TYPED_TEST(...) TYPED_TEST(__VA_ARGS__)
#define __sort insertionSort
#define __testName insertionSortCheck
#define __SortTest InsertionSortTest
#include "concrete_example.h"
#undef __sort
#define __sort selectionSort
#undef __testName
#define __testName selectionSortCheck
#undef __SortTest
#define __SortTest SelectionSortTest
#endif // CONCRETE_EXAMPLE_H


template <typename T>
class __SortTest : public ::testing::Test {};

TYPED_TEST_CASE(__SortTest, TestTypes);

MY_TYPED_TEST(__SortTest, __testName)
{
    std::vector<int> vec = makeRandomVector<int>(10);
    __sort(vec.begin(),vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(),vec.end()));
}
